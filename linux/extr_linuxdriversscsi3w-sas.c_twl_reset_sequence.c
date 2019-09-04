#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_12__ {unsigned short fw_on_ctlr_srl; unsigned short fw_on_ctlr_branch; unsigned short fw_on_ctlr_build; int /*<<< orphan*/  driver_build_low; int /*<<< orphan*/  driver_branch_low; int /*<<< orphan*/  driver_srl_low; int /*<<< orphan*/  driver_build_high; int /*<<< orphan*/  driver_branch_high; int /*<<< orphan*/  driver_srl_high; int /*<<< orphan*/  driver_version; } ;
struct TYPE_13__ {TYPE_1__ tw_compat_info; int /*<<< orphan*/  host; scalar_t__* sense_buffer_phys; } ;
typedef  TYPE_2__ TW_Device_Extension ;

/* Variables and functions */
 int TWL_CONTROLLER_READY ; 
 int /*<<< orphan*/  TWL_HOBQPH_REG_ADDR (TYPE_2__*) ; 
 int /*<<< orphan*/  TWL_HOBQPL_REG_ADDR (TYPE_2__*) ; 
 int /*<<< orphan*/  TWL_SCRPD3_REG_ADDR (TYPE_2__*) ; 
 int /*<<< orphan*/  TWL_SOFT_RESET (TYPE_2__*) ; 
 int TWL_STATUS_OVERRUN_SUBMIT ; 
 int /*<<< orphan*/  TWL_STATUS_REG_ADDR (TYPE_2__*) ; 
 int /*<<< orphan*/  TW_9750_ARCH_ID ; 
 int /*<<< orphan*/  TW_BASE_FW_BRANCH ; 
 int /*<<< orphan*/  TW_BASE_FW_BUILD ; 
 int /*<<< orphan*/  TW_BASE_FW_SRL ; 
 int /*<<< orphan*/  TW_CURRENT_DRIVER_BRANCH ; 
 int /*<<< orphan*/  TW_CURRENT_DRIVER_BUILD ; 
 int /*<<< orphan*/  TW_CURRENT_DRIVER_SRL ; 
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_DRIVER_VERSION ; 
 int /*<<< orphan*/  TW_EXTENDED_INIT_CONNECT ; 
 int /*<<< orphan*/  TW_INIT_MESSAGE_CREDITS ; 
 int TW_MAX_RESET_TRIES ; 
 int /*<<< orphan*/  TW_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int TW_Q_LENGTH ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ twl_aen_drain_queue (TYPE_2__*,int) ; 
 scalar_t__ twl_initconnection (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*,unsigned short*,unsigned short*,unsigned short*,int*) ; 
 scalar_t__ twl_poll_register (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl_reset_sequence(TW_Device_Extension *tw_dev, int soft_reset)
{
	int retval = 1;
	int i = 0;
	u32 status = 0;
	unsigned short fw_on_ctlr_srl = 0, fw_on_ctlr_arch_id = 0;
	unsigned short fw_on_ctlr_branch = 0, fw_on_ctlr_build = 0;
	u32 init_connect_result = 0;
	int tries = 0;
	int do_soft_reset = soft_reset;

	while (tries < TW_MAX_RESET_TRIES) {
		/* Do a soft reset if one is needed */
		if (do_soft_reset) {
			TWL_SOFT_RESET(tw_dev);

			/* Make sure controller is in a good state */
			if (twl_poll_register(tw_dev, TWL_SCRPD3_REG_ADDR(tw_dev), TWL_CONTROLLER_READY, 0x0, 30)) {
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x10, "Controller never went non-ready during reset sequence");
				tries++;
				continue;
			}
			if (twl_poll_register(tw_dev, TWL_SCRPD3_REG_ADDR(tw_dev), TWL_CONTROLLER_READY, TWL_CONTROLLER_READY, 60)) {
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x11, "Controller not ready during reset sequence");
				tries++;
				continue;
			}
		}

		/* Initconnect */
		if (twl_initconnection(tw_dev, TW_INIT_MESSAGE_CREDITS,
				       TW_EXTENDED_INIT_CONNECT, TW_CURRENT_DRIVER_SRL,
				       TW_9750_ARCH_ID, TW_CURRENT_DRIVER_BRANCH,
				       TW_CURRENT_DRIVER_BUILD, &fw_on_ctlr_srl,
				       &fw_on_ctlr_arch_id, &fw_on_ctlr_branch,
				       &fw_on_ctlr_build, &init_connect_result)) {
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x12, "Initconnection failed while checking SRL");
			do_soft_reset = 1;
			tries++;
			continue;
		}

		/* Load sense buffers */
		while (i < TW_Q_LENGTH) {
			writel((u32)((u64)tw_dev->sense_buffer_phys[i] >> 32), TWL_HOBQPH_REG_ADDR(tw_dev));
			writel((u32)tw_dev->sense_buffer_phys[i], TWL_HOBQPL_REG_ADDR(tw_dev));

			/* Check status for over-run after each write */
			status = readl(TWL_STATUS_REG_ADDR(tw_dev));
			if (!(status & TWL_STATUS_OVERRUN_SUBMIT))
			    i++;
		}

		/* Now check status */
		status = readl(TWL_STATUS_REG_ADDR(tw_dev));
		if (status) {
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x13, "Bad controller status after loading sense buffers");
			do_soft_reset = 1;
			tries++;
			continue;
		}

		/* Drain the AEN queue */
		if (twl_aen_drain_queue(tw_dev, soft_reset)) {
			TW_PRINTK(tw_dev->host, TW_DRIVER, 0x14, "AEN drain failed during reset sequence");
			do_soft_reset = 1;
			tries++;
			continue;
		}

		/* Load rest of compatibility struct */
		strncpy(tw_dev->tw_compat_info.driver_version, TW_DRIVER_VERSION, strlen(TW_DRIVER_VERSION));
		tw_dev->tw_compat_info.driver_srl_high = TW_CURRENT_DRIVER_SRL;
		tw_dev->tw_compat_info.driver_branch_high = TW_CURRENT_DRIVER_BRANCH;
		tw_dev->tw_compat_info.driver_build_high = TW_CURRENT_DRIVER_BUILD;
		tw_dev->tw_compat_info.driver_srl_low = TW_BASE_FW_SRL;
		tw_dev->tw_compat_info.driver_branch_low = TW_BASE_FW_BRANCH;
		tw_dev->tw_compat_info.driver_build_low = TW_BASE_FW_BUILD;
		tw_dev->tw_compat_info.fw_on_ctlr_srl = fw_on_ctlr_srl;
		tw_dev->tw_compat_info.fw_on_ctlr_branch = fw_on_ctlr_branch;
		tw_dev->tw_compat_info.fw_on_ctlr_build = fw_on_ctlr_build;

		/* If we got here, controller is in a good state */
		retval = 0;
		goto out;
	}
out:
	return retval;
}