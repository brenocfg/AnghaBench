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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; TYPE_2__ id; } ;
struct snd_ac97 {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_3D_CONTROL ; 
 int /*<<< orphan*/  AC97_SINGLE_VALUE (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ac97_cnew (int /*<<< orphan*/ *,struct snd_ac97*) ; 
 int /*<<< orphan*/ * snd_ac97_controls_3d ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int patch_sigmatel_stac9700_3d(struct snd_ac97 * ac97)
{
	struct snd_kcontrol *kctl;
	int err;

	if ((err = snd_ctl_add(ac97->bus->card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97))) < 0)
		return err;
	strcpy(kctl->id.name, "3D Control Sigmatel - Depth");
	kctl->private_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 2, 3, 0);
	snd_ac97_write_cache(ac97, AC97_3D_CONTROL, 0x0000);
	return 0;
}