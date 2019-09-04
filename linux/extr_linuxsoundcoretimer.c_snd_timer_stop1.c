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
struct snd_timer_instance {int flags; scalar_t__ pticks; int /*<<< orphan*/  ticks; int /*<<< orphan*/  cticks; int /*<<< orphan*/  active_list; int /*<<< orphan*/  ack_list; struct snd_timer* timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start ) (struct snd_timer*) ;int /*<<< orphan*/  (* stop ) (struct snd_timer*) ;} ;
struct snd_timer {int flags; int /*<<< orphan*/  lock; TYPE_2__ hw; int /*<<< orphan*/  running; TYPE_1__* card; } ;
struct TYPE_3__ {scalar_t__ shutdown; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_PAUSE ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_STOP ; 
 int SNDRV_TIMER_FLG_CHANGE ; 
 int SNDRV_TIMER_FLG_RESCHED ; 
 int SNDRV_TIMER_IFLG_PAUSED ; 
 int SNDRV_TIMER_IFLG_RUNNING ; 
 int SNDRV_TIMER_IFLG_START ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_timer_notify1 (struct snd_timer_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_reschedule (struct snd_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_timer*) ; 
 int /*<<< orphan*/  stub2 (struct snd_timer*) ; 

__attribute__((used)) static int snd_timer_stop1(struct snd_timer_instance *timeri, bool stop)
{
	struct snd_timer *timer;
	int result = 0;
	unsigned long flags;

	timer = timeri->timer;
	if (!timer)
		return -EINVAL;
	spin_lock_irqsave(&timer->lock, flags);
	if (!(timeri->flags & (SNDRV_TIMER_IFLG_RUNNING |
			       SNDRV_TIMER_IFLG_START))) {
		result = -EBUSY;
		goto unlock;
	}
	list_del_init(&timeri->ack_list);
	list_del_init(&timeri->active_list);
	if (timer->card && timer->card->shutdown)
		goto unlock;
	if (stop) {
		timeri->cticks = timeri->ticks;
		timeri->pticks = 0;
	}
	if ((timeri->flags & SNDRV_TIMER_IFLG_RUNNING) &&
	    !(--timer->running)) {
		timer->hw.stop(timer);
		if (timer->flags & SNDRV_TIMER_FLG_RESCHED) {
			timer->flags &= ~SNDRV_TIMER_FLG_RESCHED;
			snd_timer_reschedule(timer, 0);
			if (timer->flags & SNDRV_TIMER_FLG_CHANGE) {
				timer->flags &= ~SNDRV_TIMER_FLG_CHANGE;
				timer->hw.start(timer);
			}
		}
	}
	timeri->flags &= ~(SNDRV_TIMER_IFLG_RUNNING | SNDRV_TIMER_IFLG_START);
	if (stop)
		timeri->flags &= ~SNDRV_TIMER_IFLG_PAUSED;
	else
		timeri->flags |= SNDRV_TIMER_IFLG_PAUSED;
	snd_timer_notify1(timeri, stop ? SNDRV_TIMER_EVENT_STOP :
			  SNDRV_TIMER_EVENT_PAUSE);
 unlock:
	spin_unlock_irqrestore(&timer->lock, flags);
	return result;
}