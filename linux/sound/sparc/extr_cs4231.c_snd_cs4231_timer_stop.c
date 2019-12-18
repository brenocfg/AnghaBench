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
struct snd_timer {int dummy; } ;
struct snd_cs4231 {int /*<<< orphan*/  lock; int /*<<< orphan*/ * image; } ;

/* Variables and functions */
 size_t CS4231_ALT_FEATURE_1 ; 
 int /*<<< orphan*/  CS4231_TIMER_ENABLE ; 
 int /*<<< orphan*/  snd_cs4231_out (struct snd_cs4231*,size_t,int /*<<< orphan*/ ) ; 
 struct snd_cs4231* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_cs4231_timer_stop(struct snd_timer *timer)
{
	unsigned long flags;
	struct snd_cs4231 *chip = snd_timer_chip(timer);

	spin_lock_irqsave(&chip->lock, flags);
	chip->image[CS4231_ALT_FEATURE_1] &= ~CS4231_TIMER_ENABLE;
	snd_cs4231_out(chip, CS4231_ALT_FEATURE_1,
		       chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}