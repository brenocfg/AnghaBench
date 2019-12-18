#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct azx_pcm {int /*<<< orphan*/  codec; } ;
struct azx_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ prepared; } ;

/* Variables and functions */
 TYPE_1__* azx_stream (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_is_locked (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_lock (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_unlock (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup (int /*<<< orphan*/ ,struct hda_pcm_stream*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hdac_stream_cleanup (TYPE_1__*) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct hda_pcm_stream* to_hda_pcm_stream (struct snd_pcm_substream*) ; 

__attribute__((used)) static int azx_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx_dev *azx_dev = get_azx_dev(substream);
	struct hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	int err;

	/* reset BDL address */
	dsp_lock(azx_dev);
	if (!dsp_is_locked(azx_dev))
		snd_hdac_stream_cleanup(azx_stream(azx_dev));

	snd_hda_codec_cleanup(apcm->codec, hinfo, substream);

	err = snd_pcm_lib_free_pages(substream);
	azx_stream(azx_dev)->prepared = 0;
	dsp_unlock(azx_dev);
	return err;
}