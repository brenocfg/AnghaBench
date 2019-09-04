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
struct vx_core {int type; int /*<<< orphan*/  card; } ;
struct snd_vxpocket {scalar_t__ mic_level; } ;

/* Variables and functions */
#define  VX_TYPE_VXP440 129 
#define  VX_TYPE_VXPOCKET 128 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_vxpocket*) ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_control_mic_boost ; 
 int /*<<< orphan*/  vx_control_mic_level ; 
 int /*<<< orphan*/  vx_set_mic_boost (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_set_mic_level (struct vx_core*,int /*<<< orphan*/ ) ; 

int vxp_add_mic_controls(struct vx_core *_chip)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);
	int err;

	/* mute input levels */
	chip->mic_level = 0;
	switch (_chip->type) {
	case VX_TYPE_VXPOCKET:
		vx_set_mic_level(_chip, 0);
		break;
	case VX_TYPE_VXP440:
		vx_set_mic_boost(_chip, 0);
		break;
	}

	/* mic level */
	switch (_chip->type) {
	case VX_TYPE_VXPOCKET:
		if ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_mic_level, chip))) < 0)
			return err;
		break;
	case VX_TYPE_VXP440:
		if ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_mic_boost, chip))) < 0)
			return err;
		break;
	}

	return 0;
}