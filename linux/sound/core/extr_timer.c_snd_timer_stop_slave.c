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
struct snd_timer_instance {int flags; TYPE_1__* timer; int /*<<< orphan*/  active_list; int /*<<< orphan*/  ack_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_PAUSE ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_STOP ; 
 int SNDRV_TIMER_IFLG_RUNNING ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_active_lock ; 
 int /*<<< orphan*/  snd_timer_notify1 (struct snd_timer_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_timer_stop_slave(struct snd_timer_instance *timeri, bool stop)
{
	unsigned long flags;

	spin_lock_irqsave(&slave_active_lock, flags);
	if (!(timeri->flags & SNDRV_TIMER_IFLG_RUNNING)) {
		spin_unlock_irqrestore(&slave_active_lock, flags);
		return -EBUSY;
	}
	timeri->flags &= ~SNDRV_TIMER_IFLG_RUNNING;
	if (timeri->timer) {
		spin_lock(&timeri->timer->lock);
		list_del_init(&timeri->ack_list);
		list_del_init(&timeri->active_list);
		snd_timer_notify1(timeri, stop ? SNDRV_TIMER_EVENT_STOP :
				  SNDRV_TIMER_EVENT_PAUSE);
		spin_unlock(&timeri->timer->lock);
	}
	spin_unlock_irqrestore(&slave_active_lock, flags);
	return 0;
}