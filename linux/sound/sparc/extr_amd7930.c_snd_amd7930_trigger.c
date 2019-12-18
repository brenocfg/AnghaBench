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
struct snd_amd7930 {unsigned int flags; int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AMD7930_CR ; 
 scalar_t__ AMD7930_DR ; 
 int /*<<< orphan*/  AMR_MUX_MCR4 ; 
 int /*<<< orphan*/  AM_MUX_MCR4_ENABLE_INTS ; 
 int EINVAL ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  sbus_writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_amd7930_trigger(struct snd_amd7930 *amd, unsigned int flag, int cmd)
{
	unsigned long flags;
	int result = 0;

	spin_lock_irqsave(&amd->lock, flags);
	if (cmd == SNDRV_PCM_TRIGGER_START) {
		if (!(amd->flags & flag)) {
			amd->flags |= flag;

			/* Enable B channel interrupts.  */
			sbus_writeb(AMR_MUX_MCR4, amd->regs + AMD7930_CR);
			sbus_writeb(AM_MUX_MCR4_ENABLE_INTS, amd->regs + AMD7930_DR);
		}
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		if (amd->flags & flag) {
			amd->flags &= ~flag;

			/* Disable B channel interrupts.  */
			sbus_writeb(AMR_MUX_MCR4, amd->regs + AMD7930_CR);
			sbus_writeb(0, amd->regs + AMD7930_DR);
		}
	} else {
		result = -EINVAL;
	}
	spin_unlock_irqrestore(&amd->lock, flags);

	return result;
}