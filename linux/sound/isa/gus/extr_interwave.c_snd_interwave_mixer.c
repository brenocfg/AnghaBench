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
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CS4231_LEFT_MIC_INPUT ; 
 int /*<<< orphan*/  CS4231_LINE_LEFT_OUTPUT ; 
 int /*<<< orphan*/  CS4231_LINE_RIGHT_OUTPUT ; 
 int /*<<< orphan*/  CS4231_RIGHT_MIC_INPUT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_wss*) ; 
 int snd_ctl_remove_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int snd_ctl_rename_id (struct snd_card*,struct snd_ctl_elem_id*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/ * snd_interwave_controls ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_interwave_mixer(struct snd_wss *chip)
{
	struct snd_card *card = chip->card;
	struct snd_ctl_elem_id id1, id2;
	unsigned int idx;
	int err;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
#if 0
	/* remove mono microphone controls */
	strcpy(id1.name, "Mic Playback Switch");
	if ((err = snd_ctl_remove_id(card, &id1)) < 0)
		return err;
	strcpy(id1.name, "Mic Playback Volume");
	if ((err = snd_ctl_remove_id(card, &id1)) < 0)
		return err;
#endif
	/* add new master and mic controls */
	for (idx = 0; idx < ARRAY_SIZE(snd_interwave_controls); idx++)
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_interwave_controls[idx], chip))) < 0)
			return err;
	snd_wss_out(chip, CS4231_LINE_LEFT_OUTPUT, 0x9f);
	snd_wss_out(chip, CS4231_LINE_RIGHT_OUTPUT, 0x9f);
	snd_wss_out(chip, CS4231_LEFT_MIC_INPUT, 0x9f);
	snd_wss_out(chip, CS4231_RIGHT_MIC_INPUT, 0x9f);
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
	return 0;
}