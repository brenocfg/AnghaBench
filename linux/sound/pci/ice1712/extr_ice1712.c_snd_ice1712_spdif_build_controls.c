#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_6__ {struct snd_kcontrol* stream_ctl; } ;
struct snd_ice1712 {TYPE_3__ spdif; TYPE_2__* pcm_pro; int /*<<< orphan*/  card; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_spdif_default ; 
 int /*<<< orphan*/  snd_ice1712_spdif_maskc ; 
 int /*<<< orphan*/  snd_ice1712_spdif_maskp ; 
 int /*<<< orphan*/  snd_ice1712_spdif_stream ; 

int snd_ice1712_spdif_build_controls(struct snd_ice1712 *ice)
{
	int err;
	struct snd_kcontrol *kctl;

	if (snd_BUG_ON(!ice->pcm_pro))
		return -EIO;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdif_default, ice));
	if (err < 0)
		return err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdif_maskc, ice));
	if (err < 0)
		return err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdif_maskp, ice));
	if (err < 0)
		return err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdif_stream, ice));
	if (err < 0)
		return err;
	kctl->id.device = ice->pcm_pro->device;
	ice->spdif.stream_ctl = kctl;
	return 0;
}