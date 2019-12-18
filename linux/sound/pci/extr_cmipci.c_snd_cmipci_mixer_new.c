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
struct snd_kcontrol_new {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int device; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct snd_ctl_elem_id {int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct cmipci {int chip_version; scalar_t__ device; struct snd_kcontrol** mixer_res_ctl; struct snd_card* card; scalar_t__ can_ac3_hw; int /*<<< orphan*/  can_multi_ch; int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  elem_id ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct snd_kcontrol_new*) ; 
 unsigned int CM_SAVED_MIXERS ; 
 int EINVAL ; 
 scalar_t__ PCI_DEVICE_ID_CMEDIA_CM8738 ; 
 scalar_t__ PCI_DEVICE_ID_CMEDIA_CM8738B ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 TYPE_2__* cm_saved_mixer ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_kcontrol_new* snd_cmipci_8738_mixer_switches ; 
 struct snd_kcontrol_new* snd_cmipci_extra_mixer_switches ; 
 struct snd_kcontrol_new* snd_cmipci_mixer_switches ; 
 int /*<<< orphan*/  snd_cmipci_mixer_write (struct cmipci*,int,int) ; 
 struct snd_kcontrol_new* snd_cmipci_mixers ; 
 struct snd_kcontrol_new snd_cmipci_modem_switch ; 
 struct snd_kcontrol_new snd_cmipci_nomulti_switch ; 
 struct snd_kcontrol_new* snd_cmipci_old_mixer_switches ; 
 struct snd_kcontrol_new snd_cmipci_spdif_default ; 
 struct snd_kcontrol_new snd_cmipci_spdif_mask ; 
 struct snd_kcontrol_new snd_cmipci_spdif_stream ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct cmipci*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_cmipci_mixer_new(struct cmipci *cm, int pcm_spdif_device)
{
	struct snd_card *card;
	struct snd_kcontrol_new *sw;
	struct snd_kcontrol *kctl;
	unsigned int idx;
	int err;

	if (snd_BUG_ON(!cm || !cm->card))
		return -EINVAL;

	card = cm->card;

	strcpy(card->mixername, "CMedia PCI");

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_mixer_write(cm, 0x00, 0x00);		/* mixer reset */
	spin_unlock_irq(&cm->reg_lock);

	for (idx = 0; idx < ARRAY_SIZE(snd_cmipci_mixers); idx++) {
		if (cm->chip_version == 68) {	// 8768 has no PCM volume
			if (!strcmp(snd_cmipci_mixers[idx].name,
				"PCM Playback Volume"))
				continue;
		}
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cmipci_mixers[idx], cm))) < 0)
			return err;
	}

	/* mixer switches */
	sw = snd_cmipci_mixer_switches;
	for (idx = 0; idx < ARRAY_SIZE(snd_cmipci_mixer_switches); idx++, sw++) {
		err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
		if (err < 0)
			return err;
	}
	if (! cm->can_multi_ch) {
		err = snd_ctl_add(cm->card, snd_ctl_new1(&snd_cmipci_nomulti_switch, cm));
		if (err < 0)
			return err;
	}
	if (cm->device == PCI_DEVICE_ID_CMEDIA_CM8738 ||
	    cm->device == PCI_DEVICE_ID_CMEDIA_CM8738B) {
		sw = snd_cmipci_8738_mixer_switches;
		for (idx = 0; idx < ARRAY_SIZE(snd_cmipci_8738_mixer_switches); idx++, sw++) {
			err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
			if (err < 0)
				return err;
		}
		if (cm->can_ac3_hw) {
			if ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdif_default, cm))) < 0)
				return err;
			kctl->id.device = pcm_spdif_device;
			if ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdif_mask, cm))) < 0)
				return err;
			kctl->id.device = pcm_spdif_device;
			if ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdif_stream, cm))) < 0)
				return err;
			kctl->id.device = pcm_spdif_device;
		}
		if (cm->chip_version <= 37) {
			sw = snd_cmipci_old_mixer_switches;
			for (idx = 0; idx < ARRAY_SIZE(snd_cmipci_old_mixer_switches); idx++, sw++) {
				err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
				if (err < 0)
					return err;
			}
		}
	}
	if (cm->chip_version >= 39) {
		sw = snd_cmipci_extra_mixer_switches;
		for (idx = 0; idx < ARRAY_SIZE(snd_cmipci_extra_mixer_switches); idx++, sw++) {
			err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
			if (err < 0)
				return err;
		}
	}

	/* card switches */
	/*
	 * newer chips don't have the register bits to force modem link
	 * detection; the bit that was FLINKON now mutes CH1
	 */
	if (cm->chip_version < 39) {
		err = snd_ctl_add(cm->card,
				  snd_ctl_new1(&snd_cmipci_modem_switch, cm));
		if (err < 0)
			return err;
	}

	for (idx = 0; idx < CM_SAVED_MIXERS; idx++) {
		struct snd_ctl_elem_id elem_id;
		struct snd_kcontrol *ctl;
		memset(&elem_id, 0, sizeof(elem_id));
		elem_id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		strcpy(elem_id.name, cm_saved_mixer[idx].name);
		ctl = snd_ctl_find_id(cm->card, &elem_id);
		if (ctl)
			cm->mixer_res_ctl[idx] = ctl;
	}

	return 0;
}