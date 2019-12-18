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
struct snd_wss {int* image; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_hw_params {int /*<<< orphan*/  rate_den; } ;

/* Variables and functions */
 size_t CS4231_ALT_FEATURE_1 ; 
 size_t CS4231_REC_FORMAT ; 
 int /*<<< orphan*/  CS4236_ADC_RATE ; 
 unsigned char divisor_to_rate_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4236_ext_out (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4236_capture_format(struct snd_wss *chip,
				      struct snd_pcm_hw_params *params,
				      unsigned char cdfr)
{
	unsigned long flags;
	unsigned char rate = divisor_to_rate_register(params->rate_den);
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	/* set fast capture format change and clean capture FIFO */
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] | 0x20);
	snd_wss_out(chip, CS4231_REC_FORMAT, cdfr & 0xf0);
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] & ~0x20);
	snd_cs4236_ext_out(chip, CS4236_ADC_RATE, rate);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}