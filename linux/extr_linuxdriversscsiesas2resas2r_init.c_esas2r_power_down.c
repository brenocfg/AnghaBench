#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct esas2r_adapter {int /*<<< orphan*/  prev_dev_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  flags2; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_VDA_POWER_DOWN ; 
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int /*<<< orphan*/  AF_OS_RESET ; 
 int /*<<< orphan*/  AF_POWER_DOWN ; 
 int /*<<< orphan*/  AF_POWER_MGT ; 
 int DRBL_MSG_IFC_DOWN ; 
 int /*<<< orphan*/  MU_DOORBELL_IN ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_disable_heartbeat (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_power_down_notify_firmware (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_process_adapter_reset (struct esas2r_adapter*) ; 
 int esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_targ_db_get_tgt_cnt (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_targ_db_remove_all (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_power_down(struct esas2r_adapter *a)
{
	set_bit(AF_POWER_MGT, &a->flags);
	set_bit(AF_POWER_DOWN, &a->flags);

	if (!test_bit(AF_DEGRADED_MODE, &a->flags)) {
		u32 starttime;
		u32 doorbell;

		/*
		 * We are currently running OK and will be reinitializing later.
		 * increment the disable count to coordinate with
		 * esas2r_init_adapter.  We don't have to do this in degraded
		 * mode since we never enabled interrupts in the first place.
		 */
		esas2r_disable_chip_interrupts(a);
		esas2r_disable_heartbeat(a);

		/* wait for any VDA activity to clear before continuing */
		esas2r_write_register_dword(a, MU_DOORBELL_IN,
					    DRBL_MSG_IFC_DOWN);
		starttime = jiffies_to_msecs(jiffies);

		while (true) {
			doorbell =
				esas2r_read_register_dword(a, MU_DOORBELL_OUT);
			if (doorbell & DRBL_MSG_IFC_DOWN) {
				esas2r_write_register_dword(a, MU_DOORBELL_OUT,
							    doorbell);
				break;
			}

			schedule_timeout_interruptible(msecs_to_jiffies(100));

			if ((jiffies_to_msecs(jiffies) - starttime) > 3000) {
				esas2r_hdebug(
					"timeout waiting for interface down");
				break;
			}
		}

		/*
		 * For versions of firmware that support it tell them the driver
		 * is powering down.
		 */
		if (test_bit(AF2_VDA_POWER_DOWN, &a->flags2))
			esas2r_power_down_notify_firmware(a);
	}

	/* Suspend I/O processing. */
	set_bit(AF_OS_RESET, &a->flags);
	set_bit(AF_DISC_PENDING, &a->flags);
	set_bit(AF_CHPRST_PENDING, &a->flags);

	esas2r_process_adapter_reset(a);

	/* Remove devices now that I/O is cleaned up. */
	a->prev_dev_cnt = esas2r_targ_db_get_tgt_cnt(a);
	esas2r_targ_db_remove_all(a, false);
}