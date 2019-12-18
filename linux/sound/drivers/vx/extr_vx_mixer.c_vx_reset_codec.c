#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vx_core {scalar_t__ type; scalar_t__** output_level; TYPE_2__* hw; TYPE_1__* ops; } ;
struct TYPE_4__ {unsigned int num_codecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  akm_write; int /*<<< orphan*/  (* reset_codec ) (struct vx_core*) ;} ;

/* Variables and functions */
 int DAC_ATTEN_MAX ; 
 scalar_t__ VX_TYPE_VXPOCKET ; 
 int /*<<< orphan*/  XX_CODEC_ADC_CONTROL_REGISTER ; 
 int /*<<< orphan*/  XX_CODEC_CLOCK_CONTROL_REGISTER ; 
 int /*<<< orphan*/  XX_CODEC_DAC_CONTROL_REGISTER ; 
 int /*<<< orphan*/  XX_CODEC_PORT_MODE_REGISTER ; 
 int /*<<< orphan*/  stub1 (struct vx_core*) ; 
 int /*<<< orphan*/  vx_set_analog_output_level (struct vx_core*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_set_codec_reg (struct vx_core*,unsigned int,int /*<<< orphan*/ ,int) ; 

void vx_reset_codec(struct vx_core *chip, int cold_reset)
{
	unsigned int i;
	int port = chip->type >= VX_TYPE_VXPOCKET ? 0x75 : 0x65;

	chip->ops->reset_codec(chip);

	/* AKM codecs should be initialized in reset_codec callback */
	if (! chip->ops->akm_write) {
		/* initialize old codecs */
		for (i = 0; i < chip->hw->num_codecs; i++) {
			/* DAC control register (change level when zero crossing + mute) */
			vx_set_codec_reg(chip, i, XX_CODEC_DAC_CONTROL_REGISTER, DAC_ATTEN_MAX);
			/* ADC control register */
			vx_set_codec_reg(chip, i, XX_CODEC_ADC_CONTROL_REGISTER, 0x00);
			/* Port mode register */
			vx_set_codec_reg(chip, i, XX_CODEC_PORT_MODE_REGISTER, port);
			/* Clock control register */
			vx_set_codec_reg(chip, i, XX_CODEC_CLOCK_CONTROL_REGISTER, 0x00);
		}
	}

	/* mute analog output */
	for (i = 0; i < chip->hw->num_codecs; i++) {
		chip->output_level[i][0] = 0;
		chip->output_level[i][1] = 0;
		vx_set_analog_output_level(chip, i, 0, 0);
	}
}