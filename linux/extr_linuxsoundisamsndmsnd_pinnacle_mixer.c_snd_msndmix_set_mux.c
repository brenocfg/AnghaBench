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
struct snd_msnd {unsigned int recsrc; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char HDEXAR_SET_ANA_IN ; 
 unsigned char HDEXAR_SET_DAT_IN ; 
 unsigned char HDEXAR_SET_SYNTH_IN ; 
 int /*<<< orphan*/  HDEX_AUX_REQ ; 
 unsigned int MSND_MASK_DIGITAL ; 
 unsigned int MSND_MASK_IMIX ; 
 unsigned int MSND_MASK_SYNTH ; 
 int /*<<< orphan*/  snd_msnd_send_dsp_cmd (struct snd_msnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_msnd_send_word (struct snd_msnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int snd_msndmix_set_mux(struct snd_msnd *chip, int val)
{
	unsigned newrecsrc;
	int change;
	unsigned char msndbyte;

	switch (val) {
	case 0:
		newrecsrc = MSND_MASK_IMIX;
		msndbyte = HDEXAR_SET_ANA_IN;
		break;
	case 1:
		newrecsrc = MSND_MASK_SYNTH;
		msndbyte = HDEXAR_SET_SYNTH_IN;
		break;
	case 2:
		newrecsrc = MSND_MASK_DIGITAL;
		msndbyte = HDEXAR_SET_DAT_IN;
		break;
	default:
		return -EINVAL;
	}
	change  = newrecsrc != chip->recsrc;
	if (change) {
		change = 0;
		if (!snd_msnd_send_word(chip, 0, 0, msndbyte))
			if (!snd_msnd_send_dsp_cmd(chip, HDEX_AUX_REQ)) {
				chip->recsrc = newrecsrc;
				change = 1;
			}
	}
	return change;
}