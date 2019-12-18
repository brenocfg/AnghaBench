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
struct snd_miro {int hardware; TYPE_1__* aci; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct TYPE_2__ {char aci_product; int aci_version; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
#define  OPTi9XX_HW_82C924 129 
#define  OPTi9XX_HW_82C929 128 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_miro*) ; 
 int /*<<< orphan*/ * snd_miro_amp_control ; 
 int /*<<< orphan*/ * snd_miro_capture_control ; 
 int /*<<< orphan*/ * snd_miro_controls ; 
 int /*<<< orphan*/ * snd_miro_eq_controls ; 
 int /*<<< orphan*/ * snd_miro_line_control ; 
 int /*<<< orphan*/ * snd_miro_preamp_control ; 
 int /*<<< orphan*/ * snd_miro_radio_control ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_miro_mixer(struct snd_card *card,
			  struct snd_miro *miro)
{
	unsigned int idx;
	int err;

	if (snd_BUG_ON(!miro || !card))
		return -EINVAL;

	switch (miro->hardware) {
	case OPTi9XX_HW_82C924:
		strcpy(card->mixername, "ACI & OPTi924");
		break;
	case OPTi9XX_HW_82C929:
		strcpy(card->mixername, "ACI & OPTi929");
		break;
	default:
		snd_BUG();
		break;
	}

	for (idx = 0; idx < ARRAY_SIZE(snd_miro_controls); idx++) {
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_controls[idx], miro))) < 0)
			return err;
	}

	if ((miro->aci->aci_product == 'A') ||
	    (miro->aci->aci_product == 'B')) {
		/* PCM1/PCM12 with power-amp and Line 2 */
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_line_control[0], miro))) < 0)
			return err;
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_amp_control[0], miro))) < 0)
			return err;
	}

	if ((miro->aci->aci_product == 'B') ||
	    (miro->aci->aci_product == 'C')) {
		/* PCM12/PCM20 with mic-preamp */
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_preamp_control[0], miro))) < 0)
			return err;
		if (miro->aci->aci_version >= 176)
			if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_capture_control[0], miro))) < 0)
				return err;
	}

	if (miro->aci->aci_product == 'C') {
		/* PCM20 with radio and 7 band equalizer */
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_radio_control[0], miro))) < 0)
			return err;
		for (idx = 0; idx < ARRAY_SIZE(snd_miro_eq_controls); idx++) {
			if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_eq_controls[idx], miro))) < 0)
				return err;
		}
	}

	return 0;
}