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
struct special_params {int /*<<< orphan*/ * ctl_id_sync; } ;
struct snd_kcontrol {int /*<<< orphan*/  id; } ;
struct snd_bebob {int /*<<< orphan*/  card; struct special_params* maudio_special_quirk; } ;

/* Variables and functions */
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_bebob*) ; 
 int /*<<< orphan*/  special_clk_ctl ; 
 int /*<<< orphan*/  special_dig_in_iface_ctl ; 
 int /*<<< orphan*/  special_dig_out_iface_ctl ; 
 int /*<<< orphan*/  special_sync_ctl ; 

__attribute__((used)) static int add_special_controls(struct snd_bebob *bebob)
{
	struct snd_kcontrol *kctl;
	struct special_params *params = bebob->maudio_special_quirk;
	int err;

	kctl = snd_ctl_new1(&special_clk_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	if (err < 0)
		goto end;

	kctl = snd_ctl_new1(&special_sync_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	if (err < 0)
		goto end;
	params->ctl_id_sync = &kctl->id;

	kctl = snd_ctl_new1(&special_dig_in_iface_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	if (err < 0)
		goto end;

	kctl = snd_ctl_new1(&special_dig_out_iface_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
end:
	return err;
}