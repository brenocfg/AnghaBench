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
typedef  scalar_t__ u32 ;
struct esas2r_request {int dummy; } ;
struct esas2r_adapter {scalar_t__ fw_version; scalar_t__ disc_start_time; int /*<<< orphan*/  disable_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  int_mask; scalar_t__* fw_rev; int /*<<< orphan*/ * image_type; int /*<<< orphan*/ * flash_rev; struct esas2r_request* first_ae_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int /*<<< orphan*/  AF_DISC_POLLED ; 
 int /*<<< orphan*/  AF_FIRST_INIT ; 
 int /*<<< orphan*/  AF_NVR_VALID ; 
 int /*<<< orphan*/  AF_TASKLET_SCHEDULED ; 
 int /*<<< orphan*/  ESAS2R_INT_STS_MASK ; 
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
 scalar_t__ HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
 scalar_t__ LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_disc_check_for_work (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_disc_initialize (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_disc_start_waiting (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_do_deferred_processes (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_do_tasklet_tasks (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_enable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_enable_heartbeat (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*,scalar_t__*) ; 
 int /*<<< orphan*/  esas2r_init_msgs (struct esas2r_adapter*) ; 
 scalar_t__ esas2r_is_tasklet_pending (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_nvram_read_direct (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_read_flash_rev (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_read_image_type (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_set_degraded_mode (struct esas2r_adapter*,char*) ; 
 int /*<<< orphan*/  esas2r_start_ae_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_targ_db_report_changes (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_timer_tick (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ num_ae_requests ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool esas2r_init_adapter_hw(struct esas2r_adapter *a, bool init_poll)
{
	bool rslt = false;
	struct esas2r_request *rq;
	u32 i;

	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		goto exit;

	if (!test_bit(AF_NVR_VALID, &a->flags)) {
		if (!esas2r_nvram_read_direct(a))
			esas2r_log(ESAS2R_LOG_WARN,
				   "invalid/missing NVRAM parameters");
	}

	if (!esas2r_init_msgs(a)) {
		esas2r_set_degraded_mode(a, "init messages failed");
		goto exit;
	}

	/* The firmware is ready. */
	clear_bit(AF_DEGRADED_MODE, &a->flags);
	clear_bit(AF_CHPRST_PENDING, &a->flags);

	/* Post all the async event requests */
	for (i = 0, rq = a->first_ae_req; i < num_ae_requests; i++, rq++)
		esas2r_start_ae_request(a, rq);

	if (!a->flash_rev[0])
		esas2r_read_flash_rev(a);

	if (!a->image_type[0])
		esas2r_read_image_type(a);

	if (a->fw_version == 0)
		a->fw_rev[0] = 0;
	else
		sprintf(a->fw_rev, "%1d.%02d",
			(int)LOBYTE(HIWORD(a->fw_version)),
			(int)HIBYTE(HIWORD(a->fw_version)));

	esas2r_hdebug("firmware revision: %s", a->fw_rev);

	if (test_bit(AF_CHPRST_DETECTED, &a->flags)
	    && (test_bit(AF_FIRST_INIT, &a->flags))) {
		esas2r_enable_chip_interrupts(a);
		return true;
	}

	/* initialize discovery */
	esas2r_disc_initialize(a);

	/*
	 * wait for the device wait time to expire here if requested.  this is
	 * usually requested during initial driver load and possibly when
	 * resuming from a low power state.  deferred device waiting will use
	 * interrupts.  chip reset recovery always defers device waiting to
	 * avoid being in a TASKLET too long.
	 */
	if (init_poll) {
		u32 currtime = a->disc_start_time;
		u32 nexttick = 100;
		u32 deltatime;

		/*
		 * Block Tasklets from getting scheduled and indicate this is
		 * polled discovery.
		 */
		set_bit(AF_TASKLET_SCHEDULED, &a->flags);
		set_bit(AF_DISC_POLLED, &a->flags);

		/*
		 * Temporarily bring the disable count to zero to enable
		 * deferred processing.  Note that the count is already zero
		 * after the first initialization.
		 */
		if (test_bit(AF_FIRST_INIT, &a->flags))
			atomic_dec(&a->disable_cnt);

		while (test_bit(AF_DISC_PENDING, &a->flags)) {
			schedule_timeout_interruptible(msecs_to_jiffies(100));

			/*
			 * Determine the need for a timer tick based on the
			 * delta time between this and the last iteration of
			 * this loop.  We don't use the absolute time because
			 * then we would have to worry about when nexttick
			 * wraps and currtime hasn't yet.
			 */
			deltatime = jiffies_to_msecs(jiffies) - currtime;
			currtime += deltatime;

			/*
			 * Process any waiting discovery as long as the chip is
			 * up.  If a chip reset happens during initial polling,
			 * we have to make sure the timer tick processes the
			 * doorbell indicating the firmware is ready.
			 */
			if (!test_bit(AF_CHPRST_PENDING, &a->flags))
				esas2r_disc_check_for_work(a);

			/* Simulate a timer tick. */
			if (nexttick <= deltatime) {

				/* Time for a timer tick */
				nexttick += 100;
				esas2r_timer_tick(a);
			}

			if (nexttick > deltatime)
				nexttick -= deltatime;

			/* Do any deferred processing */
			if (esas2r_is_tasklet_pending(a))
				esas2r_do_tasklet_tasks(a);

		}

		if (test_bit(AF_FIRST_INIT, &a->flags))
			atomic_inc(&a->disable_cnt);

		clear_bit(AF_DISC_POLLED, &a->flags);
		clear_bit(AF_TASKLET_SCHEDULED, &a->flags);
	}


	esas2r_targ_db_report_changes(a);

	/*
	 * For cases where (a) the initialization messages processing may
	 * handle an interrupt for a port event and a discovery is waiting, but
	 * we are not waiting for devices, or (b) the device wait time has been
	 * exhausted but there is still discovery pending, start any leftover
	 * discovery in interrupt driven mode.
	 */
	esas2r_disc_start_waiting(a);

	/* Enable chip interrupts */
	a->int_mask = ESAS2R_INT_STS_MASK;
	esas2r_enable_chip_interrupts(a);
	esas2r_enable_heartbeat(a);
	rslt = true;

exit:
	/*
	 * Regardless of whether initialization was successful, certain things
	 * need to get done before we exit.
	 */

	if (test_bit(AF_CHPRST_DETECTED, &a->flags) &&
	    test_bit(AF_FIRST_INIT, &a->flags)) {
		/*
		 * Reinitialization was performed during the first
		 * initialization.  Only clear the chip reset flag so the
		 * original device polling is not cancelled.
		 */
		if (!rslt)
			clear_bit(AF_CHPRST_PENDING, &a->flags);
	} else {
		/* First initialization or a subsequent re-init is complete. */
		if (!rslt) {
			clear_bit(AF_CHPRST_PENDING, &a->flags);
			clear_bit(AF_DISC_PENDING, &a->flags);
		}


		/* Enable deferred processing after the first initialization. */
		if (test_bit(AF_FIRST_INIT, &a->flags)) {
			clear_bit(AF_FIRST_INIT, &a->flags);

			if (atomic_dec_return(&a->disable_cnt) == 0)
				esas2r_do_deferred_processes(a);
		}
	}

	return rslt;
}