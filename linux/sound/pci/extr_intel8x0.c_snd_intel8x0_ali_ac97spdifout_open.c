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
struct snd_pcm_substream {int dummy; } ;
struct intel8x0 {int /*<<< orphan*/ * ichd; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 size_t ALID_AC97SPDIFOUT ; 
 int /*<<< orphan*/  ALI_INTERFACECR ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_ALI_IF_AC97SP ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_intel8x0_pcm_open (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct intel8x0* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_intel8x0_ali_ac97spdifout_open(struct snd_pcm_substream *substream)
{
	struct intel8x0 *chip = snd_pcm_substream_chip(substream);
	unsigned int val;

	spin_lock_irq(&chip->reg_lock);
	val = igetdword(chip, ICHREG(ALI_INTERFACECR));
	val |= ICH_ALI_IF_AC97SP;
	iputdword(chip, ICHREG(ALI_INTERFACECR), val);
	/* also needs to set ALI_SC_CODEC_SPDF correctly */
	spin_unlock_irq(&chip->reg_lock);

	return snd_intel8x0_pcm_open(substream, &chip->ichd[ALID_AC97SPDIFOUT]);
}