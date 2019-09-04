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
struct snd_pcm_substream {TYPE_2__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct ct_atc_pcm* private_data; } ;
struct ct_atc_pcm {int dummy; } ;
struct ct_atc {int (* spdif_passthru_playback_prepare ) (struct ct_atc*,struct ct_atc_pcm*) ;int (* pcm_playback_prepare ) (struct ct_atc*,struct ct_atc_pcm*) ;TYPE_1__* card; } ;
struct TYPE_4__ {scalar_t__ device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IEC958 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ct_atc* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int stub1 (struct ct_atc*,struct ct_atc_pcm*) ; 
 int stub2 (struct ct_atc*,struct ct_atc_pcm*) ; 

__attribute__((used)) static int ct_pcm_playback_prepare(struct snd_pcm_substream *substream)
{
	int err;
	struct ct_atc *atc = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct ct_atc_pcm *apcm = runtime->private_data;

	if (IEC958 == substream->pcm->device)
		err = atc->spdif_passthru_playback_prepare(atc, apcm);
	else
		err = atc->pcm_playback_prepare(atc, apcm);

	if (err < 0) {
		dev_err(atc->card->dev,
			"Preparing pcm playback failed!!!\n");
		return err;
	}

	return 0;
}