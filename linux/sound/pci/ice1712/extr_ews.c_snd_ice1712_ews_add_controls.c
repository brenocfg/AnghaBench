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
struct TYPE_2__ {int subvendor; } ;
struct snd_ice1712 {int /*<<< orphan*/  card; TYPE_1__ eeprom; int /*<<< orphan*/ * cs8427; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  ICE1712_SUBDEVICE_DMX6FIRE 134 
#define  ICE1712_SUBDEVICE_EWS88D 133 
#define  ICE1712_SUBDEVICE_EWS88MT 132 
#define  ICE1712_SUBDEVICE_EWS88MT_NEW 131 
#define  ICE1712_SUBDEVICE_EWX2496 130 
#define  ICE1712_SUBDEVICE_PHASE88 129 
#define  ICE1712_SUBDEVICE_TS88 128 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/ * snd_ice1712_6fire_controls ; 
 int snd_ice1712_akm4xxx_build_controls (struct snd_ice1712*) ; 
 int /*<<< orphan*/ * snd_ice1712_ews88d_controls ; 
 int /*<<< orphan*/  snd_ice1712_ews88mt_input_sense ; 
 int /*<<< orphan*/  snd_ice1712_ews88mt_output_sense ; 
 int /*<<< orphan*/ * snd_ice1712_ewx2496_controls ; 
 int snd_ice1712_spdif_build_controls (struct snd_ice1712*) ; 

__attribute__((used)) static int snd_ice1712_ews_add_controls(struct snd_ice1712 *ice)
{
	unsigned int idx;
	int err;
	
	/* all terratec cards have spdif, but cs8427 module builds it's own controls */
	if (ice->cs8427 == NULL) {
		err = snd_ice1712_spdif_build_controls(ice);
		if (err < 0)
			return err;
	}

	/* ak4524 controls */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_EWX2496:
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
	case ICE1712_SUBDEVICE_DMX6FIRE:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
		break;
	}

	/* card specific controls */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_EWX2496:
		for (idx = 0; idx < ARRAY_SIZE(snd_ice1712_ewx2496_controls); idx++) {
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ewx2496_controls[idx], ice));
			if (err < 0)
				return err;
		}
		break;
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88mt_input_sense, ice));
		if (err < 0)
			return err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88mt_output_sense, ice));
		if (err < 0)
			return err;
		break;
	case ICE1712_SUBDEVICE_EWS88D:
		for (idx = 0; idx < ARRAY_SIZE(snd_ice1712_ews88d_controls); idx++) {
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88d_controls[idx], ice));
			if (err < 0)
				return err;
		}
		break;
	case ICE1712_SUBDEVICE_DMX6FIRE:
		for (idx = 0; idx < ARRAY_SIZE(snd_ice1712_6fire_controls); idx++) {
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_6fire_controls[idx], ice));
			if (err < 0)
				return err;
		}
		break;
	}
	return 0;
}