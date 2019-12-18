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
struct snd_pcm_runtime {int rate; int channels; int sample_bits; } ;
struct intel8x0 {int device_type; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_SCR ; 
#define  DEVICE_ALI 129 
 int DEVICE_INTEL_ICH4 ; 
 int DEVICE_NFORCE ; 
#define  DEVICE_SIS 128 
 int /*<<< orphan*/  GLOB_CNT ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_ALI_SC_PCM_246_MASK ; 
 unsigned int ICH_ALI_SC_PCM_4 ; 
 unsigned int ICH_ALI_SC_PCM_6 ; 
 unsigned int ICH_PCM_20BIT ; 
 unsigned int ICH_PCM_246_MASK ; 
 unsigned int ICH_PCM_4 ; 
 unsigned int ICH_PCM_6 ; 
 unsigned int ICH_PCM_8 ; 
 unsigned int ICH_SIS_PCM_246_MASK ; 
 unsigned int ICH_SIS_PCM_4 ; 
 unsigned int ICH_SIS_PCM_6 ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_intel8x0_setup_pcm_out(struct intel8x0 *chip,
				       struct snd_pcm_runtime *runtime)
{
	unsigned int cnt;
	int dbl = runtime->rate > 48000;

	spin_lock_irq(&chip->reg_lock);
	switch (chip->device_type) {
	case DEVICE_ALI:
		cnt = igetdword(chip, ICHREG(ALI_SCR));
		cnt &= ~ICH_ALI_SC_PCM_246_MASK;
		if (runtime->channels == 4 || dbl)
			cnt |= ICH_ALI_SC_PCM_4;
		else if (runtime->channels == 6)
			cnt |= ICH_ALI_SC_PCM_6;
		iputdword(chip, ICHREG(ALI_SCR), cnt);
		break;
	case DEVICE_SIS:
		cnt = igetdword(chip, ICHREG(GLOB_CNT));
		cnt &= ~ICH_SIS_PCM_246_MASK;
		if (runtime->channels == 4 || dbl)
			cnt |= ICH_SIS_PCM_4;
		else if (runtime->channels == 6)
			cnt |= ICH_SIS_PCM_6;
		iputdword(chip, ICHREG(GLOB_CNT), cnt);
		break;
	default:
		cnt = igetdword(chip, ICHREG(GLOB_CNT));
		cnt &= ~(ICH_PCM_246_MASK | ICH_PCM_20BIT);
		if (runtime->channels == 4 || dbl)
			cnt |= ICH_PCM_4;
		else if (runtime->channels == 6)
			cnt |= ICH_PCM_6;
		else if (runtime->channels == 8)
			cnt |= ICH_PCM_8;
		if (chip->device_type == DEVICE_NFORCE) {
			/* reset to 2ch once to keep the 6 channel data in alignment,
			 * to start from Front Left always
			 */
			if (cnt & ICH_PCM_246_MASK) {
				iputdword(chip, ICHREG(GLOB_CNT), cnt & ~ICH_PCM_246_MASK);
				spin_unlock_irq(&chip->reg_lock);
				msleep(50); /* grrr... */
				spin_lock_irq(&chip->reg_lock);
			}
		} else if (chip->device_type == DEVICE_INTEL_ICH4) {
			if (runtime->sample_bits > 16)
				cnt |= ICH_PCM_20BIT;
		}
		iputdword(chip, ICHREG(GLOB_CNT), cnt);
		break;
	}
	spin_unlock_irq(&chip->reg_lock);
}