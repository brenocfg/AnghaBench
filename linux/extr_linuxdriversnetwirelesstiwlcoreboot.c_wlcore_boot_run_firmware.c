#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ id; } ;
struct wl1271 {scalar_t__ cmd_box_addr; scalar_t__* mbox_ptr; scalar_t__ mbox_size; int /*<<< orphan*/ * ptable; TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  DEBUG_MAILBOX ; 
 int /*<<< orphan*/  ECPU_CONTROL_HALT ; 
 int EIO ; 
 int INIT_LOOP ; 
 int /*<<< orphan*/  INIT_LOOP_DELAY ; 
 size_t PART_BOOT ; 
 size_t PART_WORK ; 
 int /*<<< orphan*/  REG_CHIP_ID_B ; 
 int /*<<< orphan*/  REG_COMMAND_MAILBOX_PTR ; 
 int /*<<< orphan*/  REG_EVENT_MAILBOX_PTR ; 
 int /*<<< orphan*/  REG_INTERRUPT_ACK ; 
 int /*<<< orphan*/  REG_INTERRUPT_NO_CLEAR ; 
 scalar_t__ WL1271_ACX_INTR_INIT_COMPLETE ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int wl1271_boot_set_ecpu_ctrl (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl1271_event_unmask (struct wl1271*) ; 
 int wlcore_boot_static_data (struct wl1271*) ; 
 int wlcore_read_reg (struct wl1271*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wlcore_write_reg (struct wl1271*,int /*<<< orphan*/ ,scalar_t__) ; 

int wlcore_boot_run_firmware(struct wl1271 *wl)
{
	int loop, ret;
	u32 chip_id, intr;

	/* Make sure we have the boot partition */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	if (ret < 0)
		return ret;

	ret = wl1271_boot_set_ecpu_ctrl(wl, ECPU_CONTROL_HALT);
	if (ret < 0)
		return ret;

	ret = wlcore_read_reg(wl, REG_CHIP_ID_B, &chip_id);
	if (ret < 0)
		return ret;

	wl1271_debug(DEBUG_BOOT, "chip id after firmware boot: 0x%x", chip_id);

	if (chip_id != wl->chip.id) {
		wl1271_error("chip id doesn't match after firmware boot");
		return -EIO;
	}

	/* wait for init to complete */
	loop = 0;
	while (loop++ < INIT_LOOP) {
		udelay(INIT_LOOP_DELAY);
		ret = wlcore_read_reg(wl, REG_INTERRUPT_NO_CLEAR, &intr);
		if (ret < 0)
			return ret;

		if (intr == 0xffffffff) {
			wl1271_error("error reading hardware complete "
				     "init indication");
			return -EIO;
		}
		/* check that ACX_INTR_INIT_COMPLETE is enabled */
		else if (intr & WL1271_ACX_INTR_INIT_COMPLETE) {
			ret = wlcore_write_reg(wl, REG_INTERRUPT_ACK,
					       WL1271_ACX_INTR_INIT_COMPLETE);
			if (ret < 0)
				return ret;
			break;
		}
	}

	if (loop > INIT_LOOP) {
		wl1271_error("timeout waiting for the hardware to "
			     "complete initialization");
		return -EIO;
	}

	/* get hardware config command mail box */
	ret = wlcore_read_reg(wl, REG_COMMAND_MAILBOX_PTR, &wl->cmd_box_addr);
	if (ret < 0)
		return ret;

	wl1271_debug(DEBUG_MAILBOX, "cmd_box_addr 0x%x", wl->cmd_box_addr);

	/* get hardware config event mail box */
	ret = wlcore_read_reg(wl, REG_EVENT_MAILBOX_PTR, &wl->mbox_ptr[0]);
	if (ret < 0)
		return ret;

	wl->mbox_ptr[1] = wl->mbox_ptr[0] + wl->mbox_size;

	wl1271_debug(DEBUG_MAILBOX, "MBOX ptrs: 0x%x 0x%x",
		     wl->mbox_ptr[0], wl->mbox_ptr[1]);

	ret = wlcore_boot_static_data(wl);
	if (ret < 0) {
		wl1271_error("error getting static data");
		return ret;
	}

	/*
	 * in case of full asynchronous mode the firmware event must be
	 * ready to receive event from the command mailbox
	 */

	/* unmask required mbox events  */
	ret = wl1271_event_unmask(wl);
	if (ret < 0) {
		wl1271_error("EVENT mask setting failed");
		return ret;
	}

	/* set the working partition to its "running" mode offset */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_WORK]);

	/* firmware startup completed */
	return ret;
}