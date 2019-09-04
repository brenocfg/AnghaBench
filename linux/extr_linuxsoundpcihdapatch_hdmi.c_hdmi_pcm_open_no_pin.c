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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  rates; int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct hdmi_spec_per_cvt {int assigned; int /*<<< orphan*/  maxbps; int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  cvt_nid; } ;
struct hdmi_spec {int /*<<< orphan*/  pcm_in_use; } ;
struct hda_pcm_stream {int /*<<< orphan*/  rates; int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  maxbps; int /*<<< orphan*/  nid; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int) ; 
 int hdmi_choose_cvt (struct hda_codec*,int,int*) ; 
 int hinfo_to_pcm_index (struct hda_codec*,struct hda_pcm_stream*) ; 
 int /*<<< orphan*/  pin_cvt_fixup (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_pcm_open_no_pin(struct hda_pcm_stream *hinfo,
			 struct hda_codec *codec,
			 struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int cvt_idx, pcm_idx;
	struct hdmi_spec_per_cvt *per_cvt = NULL;
	int err;

	pcm_idx = hinfo_to_pcm_index(codec, hinfo);
	if (pcm_idx < 0)
		return -EINVAL;

	err = hdmi_choose_cvt(codec, -1, &cvt_idx);
	if (err)
		return err;

	per_cvt = get_cvt(spec, cvt_idx);
	per_cvt->assigned = 1;
	hinfo->nid = per_cvt->cvt_nid;

	pin_cvt_fixup(codec, NULL, per_cvt->cvt_nid);

	set_bit(pcm_idx, &spec->pcm_in_use);
	/* todo: setup spdif ctls assign */

	/* Initially set the converter's capabilities */
	hinfo->channels_min = per_cvt->channels_min;
	hinfo->channels_max = per_cvt->channels_max;
	hinfo->rates = per_cvt->rates;
	hinfo->formats = per_cvt->formats;
	hinfo->maxbps = per_cvt->maxbps;

	/* Store the updated parameters */
	runtime->hw.channels_min = hinfo->channels_min;
	runtime->hw.channels_max = hinfo->channels_max;
	runtime->hw.formats = hinfo->formats;
	runtime->hw.rates = hinfo->rates;

	snd_pcm_hw_constraint_step(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	return 0;
}