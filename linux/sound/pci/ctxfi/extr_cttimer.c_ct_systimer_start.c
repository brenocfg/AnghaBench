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
struct snd_pcm_runtime {int period_size; int rate; } ;
struct ct_timer_instance {int running; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; TYPE_1__* substream; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_systimer_start(struct ct_timer_instance *ti)
{
	struct snd_pcm_runtime *runtime = ti->substream->runtime;
	unsigned long flags;

	spin_lock_irqsave(&ti->lock, flags);
	ti->running = 1;
	mod_timer(&ti->timer,
		  jiffies + (runtime->period_size * HZ +
			     (runtime->rate - 1)) / runtime->rate);
	spin_unlock_irqrestore(&ti->lock, flags);
}