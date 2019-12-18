#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_gen_spec {scalar_t__* adc_nids; size_t* dyn_adc_idx; scalar_t__ cur_adc; int /*<<< orphan*/  cur_adc_format; int /*<<< orphan*/  cur_adc_stream_tag; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_hda_codec_cleanup_stream (struct hda_codec*,scalar_t__,int) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dyn_adc_pcm_resetup(struct hda_codec *codec, int cur)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t new_adc = spec->adc_nids[spec->dyn_adc_idx[cur]];

	if (spec->cur_adc && spec->cur_adc != new_adc) {
		/* stream is running, let's swap the current ADC */
		__snd_hda_codec_cleanup_stream(codec, spec->cur_adc, 1);
		spec->cur_adc = new_adc;
		snd_hda_codec_setup_stream(codec, new_adc,
					   spec->cur_adc_stream_tag, 0,
					   spec->cur_adc_format);
		return true;
	}
	return false;
}