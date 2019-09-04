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
struct snd_ctl_elem_id {int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  id2 ;
typedef  int /*<<< orphan*/  id1 ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_rename_id (struct snd_card*,struct snd_ctl_elem_id*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_gusextreme_mixer(struct snd_card *card)
{
	struct snd_ctl_elem_id id1, id2;
	int error;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDRV_CTL_ELEM_IFACE_MIXER;

	/* reassign AUX to SYNTHESIZER */
	strcpy(id1.name, "Aux Playback Volume");
	strcpy(id2.name, "Synth Playback Volume");
	error = snd_ctl_rename_id(card, &id1, &id2);
	if (error < 0)
		return error;

	/* reassign Master Playback Switch to Synth Playback Switch */
	strcpy(id1.name, "Master Playback Switch");
	strcpy(id2.name, "Synth Playback Switch");
	error = snd_ctl_rename_id(card, &id1, &id2);
	if (error < 0)
		return error;

	return 0;
}