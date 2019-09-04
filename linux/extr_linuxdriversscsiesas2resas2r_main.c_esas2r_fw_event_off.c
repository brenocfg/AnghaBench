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
struct esas2r_adapter {int fw_events_off; int /*<<< orphan*/  fw_event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
esas2r_fw_event_off(struct esas2r_adapter *a)
{
	unsigned long flags;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	a->fw_events_off = 1;
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
}