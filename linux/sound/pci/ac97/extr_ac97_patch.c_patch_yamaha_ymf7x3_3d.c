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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; TYPE_1__ id; } ;
struct snd_ac97 {TYPE_2__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_3D_CONTROL ; 
 int /*<<< orphan*/  AC97_SINGLE_VALUE (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AC97_YMF7X3_3D_MODE_SEL ; 
 struct snd_kcontrol* snd_ac97_cnew (int /*<<< orphan*/ *,struct snd_ac97*) ; 
 int /*<<< orphan*/ * snd_ac97_controls_3d ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ac97_ymf7x3_controls_speaker ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int patch_yamaha_ymf7x3_3d(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *kctl;
	int err;

	kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97);
	err = snd_ctl_add(ac97->bus->card, kctl);
	if (err < 0)
		return err;
	strcpy(kctl->id.name, "3D Control - Wide");
	kctl->private_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 9, 7, 0);
	snd_ac97_write_cache(ac97, AC97_3D_CONTROL, 0x0000);
	err = snd_ctl_add(ac97->bus->card,
			  snd_ac97_cnew(&snd_ac97_ymf7x3_controls_speaker,
					ac97));
	if (err < 0)
		return err;
	snd_ac97_write_cache(ac97, AC97_YMF7X3_3D_MODE_SEL, 0x0c00);
	return 0;
}