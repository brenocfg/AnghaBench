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
struct esas2r_sas_nvram {int dev_wait_time; int dev_wait_count; } ;
struct TYPE_2__ {int /*<<< orphan*/ * interrupt_cx; } ;
struct esas2r_adapter {int disc_wait_time; int disc_wait_cnt; scalar_t__ prev_dev_cnt; int /*<<< orphan*/  flags; TYPE_1__ general_req; int /*<<< orphan*/  disc_start_time; int /*<<< orphan*/  flags2; struct esas2r_sas_nvram* nvram; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_DEV_CNT_OK ; 
 int /*<<< orphan*/  AF2_DEV_SCAN ; 
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_DISC_IN_PROG ; 
 int /*<<< orphan*/  AF_POWER_MGT ; 
 int ESAS2R_MAX_TARGETS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_disc_check_complete (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_disc_initialize(struct esas2r_adapter *a)
{
	struct esas2r_sas_nvram *nvr = a->nvram;

	esas2r_trace_enter();

	clear_bit(AF_DISC_IN_PROG, &a->flags);
	clear_bit(AF2_DEV_SCAN, &a->flags2);
	clear_bit(AF2_DEV_CNT_OK, &a->flags2);

	a->disc_start_time = jiffies_to_msecs(jiffies);
	a->disc_wait_time = nvr->dev_wait_time * 1000;
	a->disc_wait_cnt = nvr->dev_wait_count;

	if (a->disc_wait_cnt > ESAS2R_MAX_TARGETS)
		a->disc_wait_cnt = ESAS2R_MAX_TARGETS;

	/*
	 * If we are doing chip reset or power management processing, always
	 * wait for devices.  use the NVRAM device count if it is greater than
	 * previously discovered devices.
	 */

	esas2r_hdebug("starting discovery...");

	a->general_req.interrupt_cx = NULL;

	if (test_bit(AF_CHPRST_DETECTED, &a->flags) ||
	    test_bit(AF_POWER_MGT, &a->flags)) {
		if (a->prev_dev_cnt == 0) {
			/* Don't bother waiting if there is nothing to wait
			 * for.
			 */
			a->disc_wait_time = 0;
		} else {
			/*
			 * Set the device wait count to what was previously
			 * found.  We don't care if the user only configured
			 * a time because we know the exact count to wait for.
			 * There is no need to honor the user's wishes to
			 * always wait the full time.
			 */
			a->disc_wait_cnt = a->prev_dev_cnt;

			/*
			 * bump the minimum wait time to 15 seconds since the
			 * default is 3 (system boot or the boot driver usually
			 * buys us more time).
			 */
			if (a->disc_wait_time < 15000)
				a->disc_wait_time = 15000;
		}
	}

	esas2r_trace("disc wait count: %d", a->disc_wait_cnt);
	esas2r_trace("disc wait time: %d", a->disc_wait_time);

	if (a->disc_wait_time == 0)
		esas2r_disc_check_complete(a);

	esas2r_trace_exit();
}