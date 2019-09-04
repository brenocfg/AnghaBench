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
typedef  int u16 ;
struct snd_ad1889 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_AC97_ACIC ; 
 int AD_AC97_ACIC_ACIE ; 
 int AD_AC97_ACIC_ACRD ; 
 int AD_AC97_ACIC_ASOE ; 
 int AD_AC97_ACIC_VSRM ; 
 int ad1889_readw (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writew (struct snd_ad1889*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ad1889_ac97_ready (struct snd_ad1889*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
snd_ad1889_ac97_xinit(struct snd_ad1889 *chip)
{
	u16 reg;

	reg = ad1889_readw(chip, AD_AC97_ACIC);
	reg |= AD_AC97_ACIC_ACRD;		/* Reset Disable */
	ad1889_writew(chip, AD_AC97_ACIC, reg);
	ad1889_readw(chip, AD_AC97_ACIC);	/* flush posted write */
	udelay(10);
	/* Interface Enable */
	reg |= AD_AC97_ACIC_ACIE;
	ad1889_writew(chip, AD_AC97_ACIC, reg);
	
	snd_ad1889_ac97_ready(chip);

	/* Audio Stream Output | Variable Sample Rate Mode */
	reg = ad1889_readw(chip, AD_AC97_ACIC);
	reg |= AD_AC97_ACIC_ASOE | AD_AC97_ACIC_VSRM;
	ad1889_writew(chip, AD_AC97_ACIC, reg);
	ad1889_readw(chip, AD_AC97_ACIC); /* flush posted write */

}