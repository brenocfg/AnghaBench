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
struct snd_timer_instance {int flags; TYPE_2__* timer; TYPE_1__* master; int /*<<< orphan*/  active_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  slave_active_head; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_CONTINUE ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_START ; 
 int SNDRV_TIMER_IFLG_DEAD ; 
 int SNDRV_TIMER_IFLG_RUNNING ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_active_lock ; 
 int /*<<< orphan*/  snd_timer_notify1 (struct snd_timer_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_timer_start_slave(struct snd_timer_instance *timeri,
				 bool start)
{
	unsigned long flags;
	int err;

	spin_lock_irqsave(&slave_active_lock, flags);
	if (timeri->flags & SNDRV_TIMER_IFLG_DEAD) {
		err = -EINVAL;
		goto unlock;
	}
	if (timeri->flags & SNDRV_TIMER_IFLG_RUNNING) {
		err = -EBUSY;
		goto unlock;
	}
	timeri->flags |= SNDRV_TIMER_IFLG_RUNNING;
	if (timeri->master && timeri->timer) {
		spin_lock(&timeri->timer->lock);
		list_add_tail(&timeri->active_list,
			      &timeri->master->slave_active_head);
		snd_timer_notify1(timeri, start ? SNDRV_TIMER_EVENT_START :
				  SNDRV_TIMER_EVENT_CONTINUE);
		spin_unlock(&timeri->timer->lock);
	}
	err = 1; /* delayed start */
 unlock:
	spin_unlock_irqrestore(&slave_active_lock, flags);
	return err;
}