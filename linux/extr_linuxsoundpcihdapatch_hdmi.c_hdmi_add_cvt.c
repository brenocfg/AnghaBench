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
struct hdmi_spec_per_cvt {int channels_min; unsigned int channels_max; int /*<<< orphan*/  maxbps; int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; void* cvt_nid; } ;
struct TYPE_2__ {unsigned int channels_max; } ;
struct hdmi_spec {size_t num_cvts; void** cvt_nids; TYPE_1__ chmap; int /*<<< orphan*/  cvts; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  void* hda_nid_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int ENOMEM ; 
 unsigned int get_wcaps (struct hda_codec*,void*) ; 
 unsigned int get_wcaps_channels (unsigned int) ; 
 struct hdmi_spec_per_cvt* snd_array_new (int /*<<< orphan*/ *) ; 
 int snd_hda_query_supported_pcm (struct hda_codec*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_add_cvt(struct hda_codec *codec, hda_nid_t cvt_nid)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_cvt *per_cvt;
	unsigned int chans;
	int err;

	chans = get_wcaps(codec, cvt_nid);
	chans = get_wcaps_channels(chans);

	per_cvt = snd_array_new(&spec->cvts);
	if (!per_cvt)
		return -ENOMEM;

	per_cvt->cvt_nid = cvt_nid;
	per_cvt->channels_min = 2;
	if (chans <= 16) {
		per_cvt->channels_max = chans;
		if (chans > spec->chmap.channels_max)
			spec->chmap.channels_max = chans;
	}

	err = snd_hda_query_supported_pcm(codec, cvt_nid,
					  &per_cvt->rates,
					  &per_cvt->formats,
					  &per_cvt->maxbps);
	if (err < 0)
		return err;

	if (spec->num_cvts < ARRAY_SIZE(spec->cvt_nids))
		spec->cvt_nids[spec->num_cvts] = cvt_nid;
	spec->num_cvts++;

	return 0;
}