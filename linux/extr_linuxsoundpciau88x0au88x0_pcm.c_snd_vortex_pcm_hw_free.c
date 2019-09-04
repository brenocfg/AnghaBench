#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__* pcm_vol; int /*<<< orphan*/  card; } ;
typedef  TYPE_3__ vortex_t ;
struct snd_pcm_substream {size_t number; TYPE_2__* runtime; int /*<<< orphan*/  pcm; } ;
struct TYPE_11__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  type; int /*<<< orphan*/  dir; int /*<<< orphan*/  nr_ch; } ;
typedef  TYPE_4__ stream_t ;
struct TYPE_9__ {int /*<<< orphan*/ * private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  kctl; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ VORTEX_PCM_ADB ; 
 scalar_t__ VORTEX_PCM_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VORTEX_PCM_WT ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 TYPE_3__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_adb_allocroute (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vortex_notify_pcm_vol_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_wt_allocroute (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_vortex_pcm_hw_free(struct snd_pcm_substream *substream)
{
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) (substream->runtime->private_data);

	spin_lock_irq(&chip->lock);
	// Delete audio routes.
	if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) {
		if (stream != NULL) {
			if (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB) {
				chip->pcm_vol[substream->number].active = 0;
				vortex_notify_pcm_vol_change(chip->card,
					chip->pcm_vol[substream->number].kctl,
					0);
			}
			vortex_adb_allocroute(chip, stream->dma,
					      stream->nr_ch, stream->dir,
					      stream->type,
					      substream->number);
		}
	}
#ifndef CHIP_AU8810
	else {
		if (stream != NULL)
			vortex_wt_allocroute(chip, stream->dma, 0);
	}
#endif
	substream->runtime->private_data = NULL;
	spin_unlock_irq(&chip->lock);

	return snd_pcm_lib_free_pages(substream);
}