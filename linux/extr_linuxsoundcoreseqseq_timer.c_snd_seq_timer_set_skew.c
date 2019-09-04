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
struct snd_seq_timer {unsigned int skew; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SKEW_BASE ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_timer_set_skew(struct snd_seq_timer *tmr, unsigned int skew,
			   unsigned int base)
{
	unsigned long flags;

	if (snd_BUG_ON(!tmr))
		return -EINVAL;

	/* FIXME */
	if (base != SKEW_BASE) {
		pr_debug("ALSA: seq: invalid skew base 0x%x\n", base);
		return -EINVAL;
	}
	spin_lock_irqsave(&tmr->lock, flags);
	tmr->skew = skew;
	spin_unlock_irqrestore(&tmr->lock, flags);
	return 0;
}