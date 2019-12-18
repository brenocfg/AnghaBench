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
struct tlv320dac33_priv {int fifo_mode; int /*<<< orphan*/  nsample; int /*<<< orphan*/  lock; int /*<<< orphan*/  t_stamp2; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DAC33_FIFO_MODE1 129 
#define  DAC33_FIFO_MODE7 128 
 int /*<<< orphan*/  DAC33_NSAMPLE_MSB ; 
 int /*<<< orphan*/  DAC33_THRREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write16 (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void dac33_playback_handler(struct tlv320dac33_priv *dac33)
{
	struct snd_soc_component *component = dac33->component;
	unsigned long flags;

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		/* Take the timestamp */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp2 = ktime_to_us(ktime_get());
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_write16(component, DAC33_NSAMPLE_MSB,
				DAC33_THRREG(dac33->nsample));
		break;
	case DAC33_FIFO_MODE7:
		/* At the moment we are not using interrupts in mode7 */
		break;
	default:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fifo_mode);
		break;
	}
}