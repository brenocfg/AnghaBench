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
struct snd_wss {struct snd_card* card; } ;
struct snd_ctl_elem_id {int index; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  id2 ;
typedef  int /*<<< orphan*/  id1 ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  SNDRV_MIXER_ETYPE_INPUT ; 
 int /*<<< orphan*/  SNDRV_MIXER_ETYPE_SWITCH1 ; 
 int /*<<< orphan*/  SNDRV_MIXER_ETYPE_VOLUME1 ; 
 char* SNDRV_MIXER_IN_MIC ; 
 char* SNDRV_MIXER_IN_MONO ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer ; 
 int snd_ctl_rename_id (struct snd_card*,struct snd_ctl_elem_id*,struct snd_ctl_elem_id*) ; 
 scalar_t__ snd_mixer_elem_rename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_mixer_group_rename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_gusmax_mixer(struct snd_wss *chip)
{
	struct snd_card *card = chip->card;
	struct snd_ctl_elem_id id1, id2;
	int err;
	
	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUXA to SYNTHESIZER */
	strcpy(id1.name, "Aux Playback Switch");
	strcpy(id2.name, "Synth Playback Switch");
	if ((err = snd_ctl_rename_id(card, &id1, &id2)) < 0)
		return err;
	strcpy(id1.name, "Aux Playback Volume");
	strcpy(id2.name, "Synth Playback Volume");
	if ((err = snd_ctl_rename_id(card, &id1, &id2)) < 0)
		return err;
	/* reassign AUXB to CD */
	strcpy(id1.name, "Aux Playback Switch"); id1.index = 1;
	strcpy(id2.name, "CD Playback Switch");
	if ((err = snd_ctl_rename_id(card, &id1, &id2)) < 0)
		return err;
	strcpy(id1.name, "Aux Playback Volume");
	strcpy(id2.name, "CD Playback Volume");
	if ((err = snd_ctl_rename_id(card, &id1, &id2)) < 0)
		return err;
#if 0
	/* reassign Mono Input to MIC */
	if (snd_mixer_group_rename(mixer,
				SNDRV_MIXER_IN_MONO, 0,
				SNDRV_MIXER_IN_MIC, 0) < 0)
		goto __error;
	if (snd_mixer_elem_rename(mixer,
				SNDRV_MIXER_IN_MONO, 0, SNDRV_MIXER_ETYPE_INPUT,
				SNDRV_MIXER_IN_MIC, 0) < 0)
		goto __error;
	if (snd_mixer_elem_rename(mixer,
				"Mono Capture Volume", 0, SNDRV_MIXER_ETYPE_VOLUME1,
				"Mic Capture Volume", 0) < 0)
		goto __error;
	if (snd_mixer_elem_rename(mixer,
				"Mono Capture Switch", 0, SNDRV_MIXER_ETYPE_SWITCH1,
				"Mic Capture Switch", 0) < 0)
		goto __error;
#endif
	return 0;
}