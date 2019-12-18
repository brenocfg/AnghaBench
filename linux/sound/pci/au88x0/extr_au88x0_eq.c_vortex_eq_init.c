#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  card; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int private_value; TYPE_1__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 char** EqBandLabels ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  vortex_Eqlzr_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_eq_kcontrol ; 
 int /*<<< orphan*/  vortex_eqtoggle_kcontrol ; 
 int /*<<< orphan*/  vortex_levels_kcontrol ; 

__attribute__((used)) static int vortex_eq_init(vortex_t *vortex)
{
	struct snd_kcontrol *kcontrol;
	int err, i;

	vortex_Eqlzr_init(vortex);

	if ((kcontrol =
	     snd_ctl_new1(&vortex_eqtoggle_kcontrol, vortex)) == NULL)
		return -ENOMEM;
	kcontrol->private_value = 0;
	if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
		return err;

	/* EQ gain controls */
	for (i = 0; i < 10; i++) {
		if ((kcontrol =
		     snd_ctl_new1(&vortex_eq_kcontrol, vortex)) == NULL)
			return -ENOMEM;
		snprintf(kcontrol->id.name, sizeof(kcontrol->id.name),
			"%s Playback Volume", EqBandLabels[i]);
		kcontrol->private_value = i;
		if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			return err;
		//vortex->eqctrl[i] = kcontrol;
	}
	/* EQ band levels */
	if ((kcontrol = snd_ctl_new1(&vortex_levels_kcontrol, vortex)) == NULL)
		return -ENOMEM;
	if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
		return err;

	return 0;
}