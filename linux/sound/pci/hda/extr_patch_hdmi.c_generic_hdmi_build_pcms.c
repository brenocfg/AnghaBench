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
struct hdmi_spec {int num_nids; int dev_num; int pcm_used; TYPE_1__* pcm_rec; } ;
struct hda_pcm_stream {int substreams; int /*<<< orphan*/  ops; } ;
struct hda_pcm {int own_chmap; struct hda_pcm_stream* stream; int /*<<< orphan*/  pcm_type; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_2__ {struct hda_pcm* pcm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_PCM_TYPE_HDMI ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  generic_ops ; 
 struct hda_pcm* snd_hda_codec_pcm_new (struct hda_codec*,char*,int) ; 

__attribute__((used)) static int generic_hdmi_build_pcms(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int idx;

	/*
	 * for non-mst mode, pcm number is the same as before
	 * for DP MST mode, pcm number is (nid number + dev_num - 1)
	 *  dev_num is the device entry number in a pin
	 *
	 */
	for (idx = 0; idx < spec->num_nids + spec->dev_num - 1; idx++) {
		struct hda_pcm *info;
		struct hda_pcm_stream *pstr;

		info = snd_hda_codec_pcm_new(codec, "HDMI %d", idx);
		if (!info)
			return -ENOMEM;

		spec->pcm_rec[idx].pcm = info;
		spec->pcm_used++;
		info->pcm_type = HDA_PCM_TYPE_HDMI;
		info->own_chmap = true;

		pstr = &info->stream[SNDRV_PCM_STREAM_PLAYBACK];
		pstr->substreams = 1;
		pstr->ops = generic_ops;
		/* pcm number is less than 16 */
		if (spec->pcm_used >= 16)
			break;
		/* other pstr fields are set in open */
	}

	return 0;
}