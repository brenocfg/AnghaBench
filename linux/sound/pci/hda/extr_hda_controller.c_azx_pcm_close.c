#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ;} ;
struct hda_pcm_stream {TYPE_1__ ops; } ;
struct azx_pcm {int /*<<< orphan*/  info; int /*<<< orphan*/  codec; struct azx* chip; } ;
struct azx_dev {int dummy; } ;
struct azx {int /*<<< orphan*/  open_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_release_device (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_pcm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_power_down (int /*<<< orphan*/ ) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 struct hda_pcm_stream* to_hda_pcm_stream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  trace_azx_pcm_close (struct azx*,struct azx_dev*) ; 

__attribute__((used)) static int azx_pcm_close(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	struct azx *chip = apcm->chip;
	struct azx_dev *azx_dev = get_azx_dev(substream);

	trace_azx_pcm_close(chip, azx_dev);
	mutex_lock(&chip->open_mutex);
	azx_release_device(azx_dev);
	if (hinfo->ops.close)
		hinfo->ops.close(hinfo, apcm->codec, substream);
	snd_hda_power_down(apcm->codec);
	mutex_unlock(&chip->open_mutex);
	snd_hda_codec_pcm_put(apcm->info);
	return 0;
}