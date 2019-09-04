#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; } ;
struct hda_spdif_out {unsigned short ctls; } ;
struct hda_pcm_stream {int /*<<< orphan*/  maxbps; int /*<<< orphan*/  nid; } ;
struct azx_pcm {int /*<<< orphan*/  codec; struct azx* chip; } ;
struct TYPE_8__ {unsigned int stream_tag; int /*<<< orphan*/  format_val; } ;
struct azx_dev {TYPE_2__ core; } ;
struct azx {int driver_caps; unsigned int capture_streams; TYPE_1__* card; } ;
struct TYPE_9__ {int prepared; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_CTX_WORKAROUND ; 
 int EBUSY ; 
 int EINVAL ; 
 TYPE_3__* azx_stream (struct azx_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsp_is_locked (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_lock (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_unlock (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int snd_hda_codec_prepare (int /*<<< orphan*/ ,struct hda_pcm_stream*,unsigned int,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 struct hda_spdif_out* snd_hda_spdif_out_of_nid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hdac_calc_stream_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_hdac_stream_reset (TYPE_3__*) ; 
 int snd_hdac_stream_set_params (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_stream_setup (TYPE_3__*) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct hda_pcm_stream* to_hda_pcm_stream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  trace_azx_pcm_prepare (struct azx*,struct azx_dev*) ; 

__attribute__((used)) static int azx_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx *chip = apcm->chip;
	struct azx_dev *azx_dev = get_azx_dev(substream);
	struct hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int format_val, stream_tag;
	int err;
	struct hda_spdif_out *spdif =
		snd_hda_spdif_out_of_nid(apcm->codec, hinfo->nid);
	unsigned short ctls = spdif ? spdif->ctls : 0;

	trace_azx_pcm_prepare(chip, azx_dev);
	dsp_lock(azx_dev);
	if (dsp_is_locked(azx_dev)) {
		err = -EBUSY;
		goto unlock;
	}

	snd_hdac_stream_reset(azx_stream(azx_dev));
	format_val = snd_hdac_calc_stream_format(runtime->rate,
						runtime->channels,
						runtime->format,
						hinfo->maxbps,
						ctls);
	if (!format_val) {
		dev_err(chip->card->dev,
			"invalid format_val, rate=%d, ch=%d, format=%d\n",
			runtime->rate, runtime->channels, runtime->format);
		err = -EINVAL;
		goto unlock;
	}

	err = snd_hdac_stream_set_params(azx_stream(azx_dev), format_val);
	if (err < 0)
		goto unlock;

	snd_hdac_stream_setup(azx_stream(azx_dev));

	stream_tag = azx_dev->core.stream_tag;
	/* CA-IBG chips need the playback stream starting from 1 */
	if ((chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND) &&
	    stream_tag > chip->capture_streams)
		stream_tag -= chip->capture_streams;
	err = snd_hda_codec_prepare(apcm->codec, hinfo, stream_tag,
				     azx_dev->core.format_val, substream);

 unlock:
	if (!err)
		azx_stream(azx_dev)->prepared = 1;
	dsp_unlock(azx_dev);
	return err;
}