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
struct hdmi_spec_per_cvt {int /*<<< orphan*/  cvt_nid; } ;
struct hda_pcm_stream {int channels_max; int /*<<< orphan*/  nid; } ;
struct hdmi_spec {struct hda_pcm_stream pcm_playback; TYPE_1__* pcm_rec; } ;
struct hda_pcm {struct hda_pcm_stream* stream; int /*<<< orphan*/  pcm_type; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_2__ {struct hda_pcm* pcm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_PCM_TYPE_HDMI ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int get_wcaps_channels (unsigned int) ; 
 struct hda_pcm* snd_hda_codec_pcm_new (struct hda_codec*,char*) ; 

__attribute__((used)) static int simple_playback_build_pcms(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	struct hda_pcm *info;
	unsigned int chans;
	struct hda_pcm_stream *pstr;
	struct hdmi_spec_per_cvt *per_cvt;

	per_cvt = get_cvt(spec, 0);
	chans = get_wcaps(codec, per_cvt->cvt_nid);
	chans = get_wcaps_channels(chans);

	info = snd_hda_codec_pcm_new(codec, "HDMI 0");
	if (!info)
		return -ENOMEM;
	spec->pcm_rec[0].pcm = info;
	info->pcm_type = HDA_PCM_TYPE_HDMI;
	pstr = &info->stream[SNDRV_PCM_STREAM_PLAYBACK];
	*pstr = spec->pcm_playback;
	pstr->nid = per_cvt->cvt_nid;
	if (pstr->channels_max <= 2 && chans && chans <= 16)
		pstr->channels_max = chans;

	return 0;
}