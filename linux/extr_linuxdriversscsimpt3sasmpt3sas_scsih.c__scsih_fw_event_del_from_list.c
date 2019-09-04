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
struct fw_event_work {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  fw_event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_event_work_put (struct fw_event_work*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_fw_event_del_from_list(struct MPT3SAS_ADAPTER *ioc, struct fw_event_work
	*fw_event)
{
	unsigned long flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	if (!list_empty(&fw_event->list)) {
		list_del_init(&fw_event->list);
		fw_event_work_put(fw_event);
	}
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
}