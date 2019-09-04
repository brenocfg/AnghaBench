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
struct snd_ctl_elem_id {int index; int /*<<< orphan*/  name; void* iface; } ;
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  id2 ;
typedef  int /*<<< orphan*/  id1 ;

/* Variables and functions */
 void* SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_rename_id (struct snd_card*,struct snd_ctl_elem_id*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_sc6000_mixer(struct snd_wss *chip)
{
	struct snd_card *card = chip->card;
	struct snd_ctl_elem_id id1, id2;
	int err;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	id2.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUX0 to FM */
	strcpy(id1.name, "Aux Playback Switch");
	strcpy(id2.name, "FM Playback Switch");
	err = snd_ctl_rename_id(card, &id1, &id2);
	if (err < 0)
		return err;
	strcpy(id1.name, "Aux Playback Volume");
	strcpy(id2.name, "FM Playback Volume");
	err = snd_ctl_rename_id(card, &id1, &id2);
	if (err < 0)
		return err;
	/* reassign AUX1 to CD */
	strcpy(id1.name, "Aux Playback Switch"); id1.index = 1;
	strcpy(id2.name, "CD Playback Switch");
	err = snd_ctl_rename_id(card, &id1, &id2);
	if (err < 0)
		return err;
	strcpy(id1.name, "Aux Playback Volume");
	strcpy(id2.name, "CD Playback Volume");
	err = snd_ctl_rename_id(card, &id1, &id2);
	if (err < 0)
		return err;
	return 0;
}