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
struct tlv320dac33_priv {int fifo_mode; int /*<<< orphan*/  lock; void* mode7_us_to_lthr; void* t_stamp1; int /*<<< orphan*/  alarm_threshold; int /*<<< orphan*/  burst_rate; void* t_stamp2; int /*<<< orphan*/  nsample; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC33_FIFO_IRQ_MASK ; 
#define  DAC33_FIFO_MODE1 129 
#define  DAC33_FIFO_MODE7 128 
 int /*<<< orphan*/  DAC33_MAT ; 
 int /*<<< orphan*/  DAC33_MODE7_MARGIN ; 
 int /*<<< orphan*/  DAC33_MUT ; 
 int /*<<< orphan*/  DAC33_NSAMPLE_MSB ; 
 int /*<<< orphan*/  DAC33_PREFILL_MSB ; 
 int /*<<< orphan*/  DAC33_THRREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAMPLES_TO_US (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write16 (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 void* ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void dac33_prefill_handler(struct tlv320dac33_priv *dac33)
{
	struct snd_soc_component *component = dac33->component;
	unsigned int delay;
	unsigned long flags;

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		dac33_write16(component, DAC33_NSAMPLE_MSB,
			DAC33_THRREG(dac33->nsample));

		/* Take the timestamps */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp2 = ktime_to_us(ktime_get());
		dac33->t_stamp1 = dac33->t_stamp2;
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_write16(component, DAC33_PREFILL_MSB,
				DAC33_THRREG(dac33->alarm_threshold));
		/* Enable Alarm Threshold IRQ with a delay */
		delay = SAMPLES_TO_US(dac33->burst_rate,
				     dac33->alarm_threshold) + 1000;
		usleep_range(delay, delay + 500);
		dac33_write(component, DAC33_FIFO_IRQ_MASK, DAC33_MAT);
		break;
	case DAC33_FIFO_MODE7:
		/* Take the timestamp */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp1 = ktime_to_us(ktime_get());
		/* Move back the timestamp with drain time */
		dac33->t_stamp1 -= dac33->mode7_us_to_lthr;
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_write16(component, DAC33_PREFILL_MSB,
				DAC33_THRREG(DAC33_MODE7_MARGIN));

		/* Enable Upper Threshold IRQ */
		dac33_write(component, DAC33_FIFO_IRQ_MASK, DAC33_MUT);
		break;
	default:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fifo_mode);
		break;
	}
}