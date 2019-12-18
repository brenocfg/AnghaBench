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
struct snd_ice1712 {TYPE_1__ eeprom; int /*<<< orphan*/  card; } ;

/* Variables and functions */
#define  ICE1712_SUBDEVICE_AUDIOPHILE 139 
#define  ICE1712_SUBDEVICE_DELTA1010 138 
#define  ICE1712_SUBDEVICE_DELTA1010E 137 
#define  ICE1712_SUBDEVICE_DELTA1010LT 136 
#define  ICE1712_SUBDEVICE_DELTA410 135 
#define  ICE1712_SUBDEVICE_DELTA44 134 
#define  ICE1712_SUBDEVICE_DELTA66 133 
#define  ICE1712_SUBDEVICE_DELTA66E 132 
#define  ICE1712_SUBDEVICE_DELTADIO2496 131 
#define  ICE1712_SUBDEVICE_EDIROLDA2496 130 
#define  ICE1712_SUBDEVICE_MEDIASTATION 129 
#define  ICE1712_SUBDEVICE_VX442 128 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int snd_ice1712_akm4xxx_build_controls (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_delta1010_wordclock_select ; 
 int /*<<< orphan*/  snd_ice1712_delta1010_wordclock_status ; 
 int /*<<< orphan*/  snd_ice1712_delta1010lt_wordclock_select ; 
 int /*<<< orphan*/  snd_ice1712_delta1010lt_wordclock_status ; 
 int /*<<< orphan*/  snd_ice1712_delta_spdif_in_status ; 
 int /*<<< orphan*/  snd_ice1712_deltadio2496_spdif_in_select ; 
 int snd_ice1712_spdif_build_controls (struct snd_ice1712*) ; 

__attribute__((used)) static int snd_ice1712_delta_add_controls(struct snd_ice1712 *ice)
{
	int err;

	/* 1010 and dio specific controls */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010_wordclock_select, ice));
		if (err < 0)
			return err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010_wordclock_status, ice));
		if (err < 0)
			return err;
		break;
	case ICE1712_SUBDEVICE_DELTADIO2496:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_deltadio2496_spdif_in_select, ice));
		if (err < 0)
			return err;
		break;
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTA1010LT:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010lt_wordclock_select, ice));
		if (err < 0)
			return err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010lt_wordclock_status, ice));
		if (err < 0)
			return err;
		break;
	}

	/* normal spdif controls */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_DELTADIO2496:
	case ICE1712_SUBDEVICE_DELTA66:
	case ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ice1712_spdif_build_controls(ice);
		if (err < 0)
			return err;
		break;
	}

	/* spdif status in */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_DELTADIO2496:
	case ICE1712_SUBDEVICE_DELTA66:
	case ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta_spdif_in_status, ice));
		if (err < 0)
			return err;
		break;
	}

	/* ak4524 controls */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010LT:
	case ICE1712_SUBDEVICE_AUDIOPHILE:
	case ICE1712_SUBDEVICE_DELTA410:
	case ICE1712_SUBDEVICE_DELTA44:
	case ICE1712_SUBDEVICE_DELTA66:
	case ICE1712_SUBDEVICE_VX442:
	case ICE1712_SUBDEVICE_DELTA66E:
	case ICE1712_SUBDEVICE_EDIROLDA2496:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
		break;
	}

	return 0;
}