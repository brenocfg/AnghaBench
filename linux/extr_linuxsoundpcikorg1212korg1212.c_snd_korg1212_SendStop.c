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
struct snd_korg1212 {int /*<<< orphan*/  timer; scalar_t__ stop_pending_cnt; TYPE_1__* sharedBufferPtr; } ;
struct TYPE_2__ {int cardCommand; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void snd_korg1212_SendStop(struct snd_korg1212 *korg1212)
{
	if (! korg1212->stop_pending_cnt) {
		korg1212->sharedBufferPtr->cardCommand = 0xffffffff;
		/* program the timer */
		korg1212->stop_pending_cnt = HZ;
		mod_timer(&korg1212->timer, jiffies + 1);
	}
}