#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct azx_pcm {int /*<<< orphan*/  codec; struct azx* chip; } ;
struct azx_dev {int dummy; } ;
struct azx {TYPE_1__* ops; } ;
struct TYPE_5__ {scalar_t__ prepared; } ;
struct TYPE_4__ {int (* substream_free_pages ) (struct azx*,struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 TYPE_2__* azx_stream (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_is_locked (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_lock (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_unlock (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup (int /*<<< orphan*/ ,struct hda_pcm_stream*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hdac_stream_cleanup (TYPE_2__*) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int stub1 (struct azx*,struct snd_pcm_substream*) ; 
 struct hda_pcm_stream* to_hda_pcm_stream (struct snd_pcm_substream*) ; 

__attribute__((used)) static int azx_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx_dev *azx_dev = get_azx_dev(substream);
	struct azx *chip = apcm->chip;
	struct hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	int err;

	/* reset BDL address */
	dsp_lock(azx_dev);
	if (!dsp_is_locked(azx_dev))
		snd_hdac_stream_cleanup(azx_stream(azx_dev));

	snd_hda_codec_cleanup(apcm->codec, hinfo, substream);

	err = chip->ops->substream_free_pages(chip, substream);
	azx_stream(azx_dev)->prepared = 0;
	dsp_unlock(azx_dev);
	return err;
}