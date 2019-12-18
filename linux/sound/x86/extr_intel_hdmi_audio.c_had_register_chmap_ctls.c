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
struct snd_pcm {int dummy; } ;
struct snd_intelhad {TYPE_2__* chmap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * chmap; TYPE_1__* kctl; struct snd_intelhad* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  get; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  had_chmap_ctl_get ; 
 int /*<<< orphan*/  had_chmap_ctl_info ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,TYPE_2__**) ; 

__attribute__((used)) static int had_register_chmap_ctls(struct snd_intelhad *intelhaddata,
						struct snd_pcm *pcm)
{
	int err;

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			NULL, 0, (unsigned long)intelhaddata,
			&intelhaddata->chmap);
	if (err < 0)
		return err;

	intelhaddata->chmap->private_data = intelhaddata;
	intelhaddata->chmap->kctl->info = had_chmap_ctl_info;
	intelhaddata->chmap->kctl->get = had_chmap_ctl_get;
	intelhaddata->chmap->chmap = NULL;
	return 0;
}