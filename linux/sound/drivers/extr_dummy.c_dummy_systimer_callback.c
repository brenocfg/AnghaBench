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
struct timer_list {int dummy; } ;
struct dummy_systimer_pcm {int elapsed; int /*<<< orphan*/  substream; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct dummy_systimer_pcm* dpcm ; 
 int /*<<< orphan*/  dummy_systimer_rearm (struct dummy_systimer_pcm*) ; 
 int /*<<< orphan*/  dummy_systimer_update (struct dummy_systimer_pcm*) ; 
 struct dummy_systimer_pcm* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void dummy_systimer_callback(struct timer_list *t)
{
	struct dummy_systimer_pcm *dpcm = from_timer(dpcm, t, timer);
	unsigned long flags;
	int elapsed = 0;
	
	spin_lock_irqsave(&dpcm->lock, flags);
	dummy_systimer_update(dpcm);
	dummy_systimer_rearm(dpcm);
	elapsed = dpcm->elapsed;
	dpcm->elapsed = 0;
	spin_unlock_irqrestore(&dpcm->lock, flags);
	if (elapsed)
		snd_pcm_period_elapsed(dpcm->substream);
}