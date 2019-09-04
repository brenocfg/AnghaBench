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
struct snic {int /*<<< orphan*/  link_work; int /*<<< orphan*/  snic_lock; scalar_t__ stop_link_events; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* snic_glob ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snic_handle_link_event(struct snic *snic)
{
	unsigned long flags;

	spin_lock_irqsave(&snic->snic_lock, flags);
	if (snic->stop_link_events) {
		spin_unlock_irqrestore(&snic->snic_lock, flags);

		return;
	}
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	queue_work(snic_glob->event_q, &snic->link_work);
}