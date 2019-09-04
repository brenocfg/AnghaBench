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
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int vt1720; int akm_codecs; TYPE_1__ eeprom; struct snd_akm4xxx* akm; } ;
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  VT1724_SUBDEVICE_PHASE22 129 
#define  VT1724_SUBDEVICE_TS22 128 
 int /*<<< orphan*/  akm_phase22 ; 
 int /*<<< orphan*/  akm_phase22_priv ; 
 struct snd_akm4xxx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_ice1712_akm4xxx_init (struct snd_akm4xxx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snd_ice1712*) ; 

__attribute__((used)) static int phase22_init(struct snd_ice1712 *ice)
{
	struct snd_akm4xxx *ak;
	int err;

	/* Configure DAC/ADC description for generic part of ice1724 */
	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_PHASE22:
	case VT1724_SUBDEVICE_TS22:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		ice->vt1720 = 1; /* Envy24HT-S have 16 bit wide GPIO */
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}

	/* Initialize analog chips */
	ice->akm = kzalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	ak = ice->akm;
	if (!ak)
		return -ENOMEM;
	ice->akm_codecs = 1;
	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_PHASE22:
	case VT1724_SUBDEVICE_TS22:
		err = snd_ice1712_akm4xxx_init(ak, &akm_phase22,
						&akm_phase22_priv, ice);
		if (err < 0)
			return err;
		break;
	}

	return 0;
}