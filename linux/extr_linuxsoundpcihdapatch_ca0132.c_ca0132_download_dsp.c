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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ dsp_state; int /*<<< orphan*/  use_alt_functions; } ;

/* Variables and functions */
 scalar_t__ DSP_DOWNLOADED ; 
 scalar_t__ DSP_DOWNLOADING ; 
 scalar_t__ DSP_DOWNLOAD_FAILED ; 
 int /*<<< orphan*/  ca0132_download_dsp_images (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_set_dsp_msr (struct hda_codec*,int) ; 
 int /*<<< orphan*/  chipio_enable_clocks (struct hda_codec*) ; 

__attribute__((used)) static void ca0132_download_dsp(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

#ifndef CONFIG_SND_HDA_CODEC_CA0132_DSP
	return; /* NOP */
#endif

	if (spec->dsp_state == DSP_DOWNLOAD_FAILED)
		return; /* don't retry failures */

	chipio_enable_clocks(codec);
	if (spec->dsp_state != DSP_DOWNLOADED) {
		spec->dsp_state = DSP_DOWNLOADING;

		if (!ca0132_download_dsp_images(codec))
			spec->dsp_state = DSP_DOWNLOAD_FAILED;
		else
			spec->dsp_state = DSP_DOWNLOADED;
	}

	/* For codecs using alt functions, this is already done earlier */
	if (spec->dsp_state == DSP_DOWNLOADED && (!spec->use_alt_functions))
		ca0132_set_dsp_msr(codec, true);
}