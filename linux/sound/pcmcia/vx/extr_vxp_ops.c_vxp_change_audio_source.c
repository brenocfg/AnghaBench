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
struct vx_core {int /*<<< orphan*/  type; } ;
struct snd_vxpocket {int /*<<< orphan*/  mic_level; int /*<<< orphan*/  regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int /*<<< orphan*/  MICRO ; 
 int /*<<< orphan*/  P24_CDSP_MIC20_SEL_MASK ; 
 int /*<<< orphan*/  P24_CDSP_MIC38_SEL_MASK ; 
 int /*<<< orphan*/  P24_CDSP_MICS_SEL_MASK ; 
 int /*<<< orphan*/  VXP_CDSP_DATAIN_SEL_MASK ; 
 int /*<<< orphan*/  VXP_CDSP_MIC_SEL_MASK ; 
#define  VX_AUDIO_SRC_DIGITAL 130 
#define  VX_AUDIO_SRC_LINE 129 
#define  VX_AUDIO_SRC_MIC 128 
 int /*<<< orphan*/  VX_TYPE_VXP440 ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_compute_mic_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outb (struct snd_vxpocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxp_change_audio_source(struct vx_core *_chip, int src)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);

	switch (src) {
	case VX_AUDIO_SRC_DIGITAL:
		chip->regCDSP |= VXP_CDSP_DATAIN_SEL_MASK;
		vx_outb(chip, CDSP, chip->regCDSP);
		break;
	case VX_AUDIO_SRC_LINE:
		chip->regCDSP &= ~VXP_CDSP_DATAIN_SEL_MASK;
		if (_chip->type == VX_TYPE_VXP440)
			chip->regCDSP &= ~P24_CDSP_MICS_SEL_MASK;
		else
			chip->regCDSP &= ~VXP_CDSP_MIC_SEL_MASK;
		vx_outb(chip, CDSP, chip->regCDSP);
		break;
	case VX_AUDIO_SRC_MIC:
		chip->regCDSP &= ~VXP_CDSP_DATAIN_SEL_MASK;
		/* reset mic levels */
		if (_chip->type == VX_TYPE_VXP440) {
			chip->regCDSP &= ~P24_CDSP_MICS_SEL_MASK;
			if (chip->mic_level)
				chip->regCDSP |=  P24_CDSP_MIC38_SEL_MASK;
			else
				chip->regCDSP |= P24_CDSP_MIC20_SEL_MASK;
			vx_outb(chip, CDSP, chip->regCDSP);
		} else {
			chip->regCDSP |= VXP_CDSP_MIC_SEL_MASK;
			vx_outb(chip, CDSP, chip->regCDSP);
			vx_outb(chip, MICRO, vx_compute_mic_level(chip->mic_level));
		}
		break;
	}
}