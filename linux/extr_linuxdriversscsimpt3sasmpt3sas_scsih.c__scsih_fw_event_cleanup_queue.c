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
struct fw_event_work {int /*<<< orphan*/  work; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  firmware_event_thread; int /*<<< orphan*/  fw_event_list; } ;

/* Variables and functions */
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct fw_event_work* dequeue_next_fw_event (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  fw_event_work_put (struct fw_event_work*) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_scsih_fw_event_cleanup_queue(struct MPT3SAS_ADAPTER *ioc)
{
	struct fw_event_work *fw_event;

	if (list_empty(&ioc->fw_event_list) ||
	     !ioc->firmware_event_thread || in_interrupt())
		return;

	while ((fw_event = dequeue_next_fw_event(ioc))) {
		/*
		 * Wait on the fw_event to complete. If this returns 1, then
		 * the event was never executed, and we need a put for the
		 * reference the work had on the fw_event.
		 *
		 * If it did execute, we wait for it to finish, and the put will
		 * happen from _firmware_event_work()
		 */
		if (cancel_work_sync(&fw_event->work))
			fw_event_work_put(fw_event);

		fw_event_work_put(fw_event);
	}
}