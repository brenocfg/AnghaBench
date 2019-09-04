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
struct vx_core {int regCDSP; scalar_t__ type; int regSELMIC; } ;
struct snd_vx222 {int regCDSP; scalar_t__ type; int regSELMIC; } ;

/* Variables and functions */
 int /*<<< orphan*/  AKM_CODEC_CLOCK_FORMAT_CMD ; 
 int /*<<< orphan*/  AKM_CODEC_MUTE_CMD ; 
 int /*<<< orphan*/  AKM_CODEC_POWER_CONTROL_CMD ; 
 int /*<<< orphan*/  AKM_CODEC_RESET_OFF_CMD ; 
 int /*<<< orphan*/  CDSP ; 
 int MICRO_SELECT_INPUT_NORM ; 
 int MICRO_SELECT_NOISE_T_52DB ; 
 int MICRO_SELECT_PHANTOM_ALIM ; 
 int MICRO_SELECT_PREAMPLI_G_0 ; 
 int /*<<< orphan*/  SELMIC ; 
 int VX_CDSP_CODEC_RESET_MASK ; 
 scalar_t__ VX_TYPE_BOARD ; 
 scalar_t__ VX_TYPE_MIC ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct vx_core* to_vx222 (struct vx_core*) ; 
 int /*<<< orphan*/  vx2_write_codec_reg (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_inl (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx2_reset_codec(struct vx_core *_chip)
{
	struct snd_vx222 *chip = to_vx222(_chip);

	/* Set the reset CODEC bit to 0. */
	vx_outl(chip, CDSP, chip->regCDSP &~ VX_CDSP_CODEC_RESET_MASK);
	vx_inl(chip, CDSP);
	msleep(10);
	/* Set the reset CODEC bit to 1. */
	chip->regCDSP |= VX_CDSP_CODEC_RESET_MASK;
	vx_outl(chip, CDSP, chip->regCDSP);
	vx_inl(chip, CDSP);
	if (_chip->type == VX_TYPE_BOARD) {
		msleep(1);
		return;
	}

	msleep(5);  /* additionnel wait time for AKM's */

	vx2_write_codec_reg(_chip, AKM_CODEC_POWER_CONTROL_CMD); /* DAC power up, ADC power up, Vref power down */
	
	vx2_write_codec_reg(_chip, AKM_CODEC_CLOCK_FORMAT_CMD); /* default */
	vx2_write_codec_reg(_chip, AKM_CODEC_MUTE_CMD); /* Mute = ON ,Deemphasis = OFF */
	vx2_write_codec_reg(_chip, AKM_CODEC_RESET_OFF_CMD); /* DAC and ADC normal operation */

	if (_chip->type == VX_TYPE_MIC) {
		/* set up the micro input selector */
		chip->regSELMIC =  MICRO_SELECT_INPUT_NORM |
			MICRO_SELECT_PREAMPLI_G_0 |
			MICRO_SELECT_NOISE_T_52DB;

		/* reset phantom power supply */
		chip->regSELMIC &= ~MICRO_SELECT_PHANTOM_ALIM;

		vx_outl(_chip, SELMIC, chip->regSELMIC);
	}
}