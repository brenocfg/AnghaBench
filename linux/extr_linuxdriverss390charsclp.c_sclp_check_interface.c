#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int response_code; } ;
struct init_sccb {TYPE_1__ header; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  command; scalar_t__ sccb; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  EXT_IRQ_SERVICE_SIG ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_SUBCLASS_SERVICE_SIGNAL ; 
 int SCLP_INIT_RETRY ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_RUNNING ; 
 int SCLP_RETRY_INTERVAL ; 
 int /*<<< orphan*/  __sclp_make_init_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sclp_set_request_timer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_subclass_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_subclass_unregister (int /*<<< orphan*/ ) ; 
 int register_external_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_check_handler ; 
 int /*<<< orphan*/  sclp_check_timeout ; 
 TYPE_2__ sclp_init_req ; 
 int /*<<< orphan*/  sclp_lock ; 
 int sclp_mask_compat_mode ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 int /*<<< orphan*/  sclp_running_state ; 
 int /*<<< orphan*/  sclp_running_state_running ; 
 int sclp_service_call (int /*<<< orphan*/ ,struct init_sccb*) ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unregister_external_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sclp_check_interface(void)
{
	struct init_sccb *sccb;
	unsigned long flags;
	int retry;
	int rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Prepare init mask command */
	rc = register_external_irq(EXT_IRQ_SERVICE_SIG, sclp_check_handler);
	if (rc) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return rc;
	}
	for (retry = 0; retry <= SCLP_INIT_RETRY; retry++) {
		__sclp_make_init_req(0, 0);
		sccb = (struct init_sccb *) sclp_init_req.sccb;
		rc = sclp_service_call(sclp_init_req.command, sccb);
		if (rc == -EIO)
			break;
		sclp_init_req.status = SCLP_REQ_RUNNING;
		sclp_running_state = sclp_running_state_running;
		__sclp_set_request_timer(SCLP_RETRY_INTERVAL * HZ,
					 sclp_check_timeout);
		spin_unlock_irqrestore(&sclp_lock, flags);
		/* Enable service-signal interruption - needs to happen
		 * with IRQs enabled. */
		irq_subclass_register(IRQ_SUBCLASS_SERVICE_SIGNAL);
		/* Wait for signal from interrupt or timeout */
		sclp_sync_wait();
		/* Disable service-signal interruption - needs to happen
		 * with IRQs enabled. */
		irq_subclass_unregister(IRQ_SUBCLASS_SERVICE_SIGNAL);
		spin_lock_irqsave(&sclp_lock, flags);
		del_timer(&sclp_request_timer);
		rc = -EBUSY;
		if (sclp_init_req.status == SCLP_REQ_DONE) {
			if (sccb->header.response_code == 0x20) {
				rc = 0;
				break;
			} else if (sccb->header.response_code == 0x74f0) {
				if (!sclp_mask_compat_mode) {
					sclp_mask_compat_mode = true;
					retry = 0;
				}
			}
		}
	}
	unregister_external_irq(EXT_IRQ_SERVICE_SIG, sclp_check_handler);
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}