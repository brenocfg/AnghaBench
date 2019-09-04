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
struct snd_ps3_card_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_AUDIO_AO_3WMCTRL ; 
 int PS3_AUDIO_AO_3WMCTRL_ASOBCLKD_DISABLED ; 
 int PS3_AUDIO_AO_3WMCTRL_ASOLRCKD_DISABLED ; 
 int /*<<< orphan*/  PS3_AUDIO_AO_3WMCTRL_ASOPLRCK_DEFAULT ; 
 int /*<<< orphan*/  PS3_AUDIO_AX_IC ; 
 int /*<<< orphan*/  PS3_AUDIO_AX_IC_AASOIMD_EVERY4 ; 
 int PS3_AUDIO_AX_IC_AASOIMD_MASK ; 
 int /*<<< orphan*/  PS3_AUDIO_INTR_EN_0 ; 
 int /*<<< orphan*/  update_mask_reg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ps3_audio_fixup(struct snd_ps3_card_info *card)
{
	/*
	 * avsetting driver seems to never change the following
	 * so, init them here once
	 */

	/* no dma interrupt needed */
	write_reg(PS3_AUDIO_INTR_EN_0, 0);

	/* use every 4 buffer empty interrupt */
	update_mask_reg(PS3_AUDIO_AX_IC,
			PS3_AUDIO_AX_IC_AASOIMD_MASK,
			PS3_AUDIO_AX_IC_AASOIMD_EVERY4);

	/* enable 3wire clocks */
	update_mask_reg(PS3_AUDIO_AO_3WMCTRL,
			~(PS3_AUDIO_AO_3WMCTRL_ASOBCLKD_DISABLED |
			  PS3_AUDIO_AO_3WMCTRL_ASOLRCKD_DISABLED),
			0);
	update_reg(PS3_AUDIO_AO_3WMCTRL,
		   PS3_AUDIO_AO_3WMCTRL_ASOPLRCK_DEFAULT);
}