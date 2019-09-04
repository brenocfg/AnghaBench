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
struct snd_pcm_substream {int dummy; } ;
struct intel8x0 {int /*<<< orphan*/  reg_lock; TYPE_1__* ichd; } ;
struct TYPE_2__ {int /*<<< orphan*/ * substream; } ;

/* Variables and functions */
 size_t ALID_AC97SPDIFOUT ; 
 int /*<<< orphan*/  ALI_INTERFACECR ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_ALI_IF_AC97SP ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 struct intel8x0* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_intel8x0_ali_ac97spdifout_close(struct snd_pcm_substream *substream)
{
	struct intel8x0 *chip = snd_pcm_substream_chip(substream);
	unsigned int val;

	chip->ichd[ALID_AC97SPDIFOUT].substream = NULL;
	spin_lock_irq(&chip->reg_lock);
	val = igetdword(chip, ICHREG(ALI_INTERFACECR));
	val &= ~ICH_ALI_IF_AC97SP;
	iputdword(chip, ICHREG(ALI_INTERFACECR), val);
	spin_unlock_irq(&chip->reg_lock);

	return 0;
}