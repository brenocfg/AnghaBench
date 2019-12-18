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
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct emu10k1x {struct snd_card* card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct emu10k1x*) ; 
 int /*<<< orphan*/  snd_emu10k1x_shared_spdif ; 
 int /*<<< orphan*/  snd_emu10k1x_spdif_control ; 
 int /*<<< orphan*/  snd_emu10k1x_spdif_mask_control ; 

__attribute__((used)) static int snd_emu10k1x_mixer(struct emu10k1x *emu)
{
	int err;
	struct snd_kcontrol *kctl;
	struct snd_card *card = emu->card;

	if ((kctl = snd_ctl_new1(&snd_emu10k1x_spdif_mask_control, emu)) == NULL)
		return -ENOMEM;
	if ((err = snd_ctl_add(card, kctl)))
		return err;
	if ((kctl = snd_ctl_new1(&snd_emu10k1x_shared_spdif, emu)) == NULL)
		return -ENOMEM;
	if ((err = snd_ctl_add(card, kctl)))
		return err;
	if ((kctl = snd_ctl_new1(&snd_emu10k1x_spdif_control, emu)) == NULL)
		return -ENOMEM;
	if ((err = snd_ctl_add(card, kctl)))
		return err;

	return 0;
}