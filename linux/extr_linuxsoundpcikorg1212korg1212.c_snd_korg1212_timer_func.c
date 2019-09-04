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
struct timer_list {int dummy; } ;
struct snd_korg1212 {scalar_t__ stop_pending_cnt; int dsp_stop_is_processed; size_t cardState; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_1__* sharedBufferPtr; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {scalar_t__ cardCommand; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK_VERBOSE (char*,int /*<<< orphan*/ ) ; 
 struct snd_korg1212* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct snd_korg1212* korg1212 ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * stateName ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_korg1212_timer_func(struct timer_list *t)
{
	struct snd_korg1212 *korg1212 = from_timer(korg1212, t, timer);
	unsigned long flags;
	
	spin_lock_irqsave(&korg1212->lock, flags);
	if (korg1212->sharedBufferPtr->cardCommand == 0) {
		/* ack'ed */
		korg1212->stop_pending_cnt = 0;
		korg1212->dsp_stop_is_processed = 1;
		wake_up(&korg1212->wait);
		K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: Stop ack'ed [%s]\n",
					   stateName[korg1212->cardState]);
	} else {
		if (--korg1212->stop_pending_cnt > 0) {
			/* reprogram timer */
			mod_timer(&korg1212->timer, jiffies + 1);
		} else {
			snd_printd("korg1212_timer_func timeout\n");
			korg1212->sharedBufferPtr->cardCommand = 0;
			korg1212->dsp_stop_is_processed = 1;
			wake_up(&korg1212->wait);
			K1212_DEBUG_PRINTK("K1212_DEBUG: Stop timeout [%s]\n",
					   stateName[korg1212->cardState]);
		}
	}
	spin_unlock_irqrestore(&korg1212->lock, flags);
}