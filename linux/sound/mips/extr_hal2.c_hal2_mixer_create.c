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
struct snd_hal2 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2I_ADC_C2 ; 
 int H2I_C2_L_ATT_M ; 
 int H2I_C2_MUTE ; 
 int H2I_C2_R_ATT_M ; 
 int /*<<< orphan*/  H2I_DAC_C2 ; 
 int /*<<< orphan*/  hal2_ctrl_headphone ; 
 int /*<<< orphan*/  hal2_ctrl_mic ; 
 int /*<<< orphan*/  hal2_i_write32 (struct snd_hal2*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_hal2*) ; 

__attribute__((used)) static int hal2_mixer_create(struct snd_hal2 *hal2)
{
	int err;

	/* mute DAC */
	hal2_i_write32(hal2, H2I_DAC_C2,
		       H2I_C2_L_ATT_M | H2I_C2_R_ATT_M | H2I_C2_MUTE);
	/* mute ADC */
	hal2_i_write32(hal2, H2I_ADC_C2, 0);

	err = snd_ctl_add(hal2->card,
			  snd_ctl_new1(&hal2_ctrl_headphone, hal2));
	if (err < 0)
		return err;

	err = snd_ctl_add(hal2->card,
			  snd_ctl_new1(&hal2_ctrl_mic, hal2));
	if (err < 0)
		return err;

	return 0;
}