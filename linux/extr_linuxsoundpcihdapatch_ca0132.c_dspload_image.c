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
struct hda_codec {int dummy; } ;
struct dsp_image_seg {int dummy; } ;

/* Variables and functions */
 int DMA_OVERLAY_FRAME_SIZE_NWORDS ; 
 int DMA_TRANSFER_FRAME_SIZE_NWORDS ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int dsp_reset (struct hda_codec*) ; 
 int dsp_set_run_state (struct hda_codec*) ; 
 int /*<<< orphan*/  dspload_post_setup (struct hda_codec*) ; 
 int dspxfr_image (struct hda_codec*,struct dsp_image_seg const*,unsigned int,unsigned int,unsigned short,int) ; 

__attribute__((used)) static int dspload_image(struct hda_codec *codec,
			const struct dsp_image_seg *fls,
			bool ovly,
			unsigned int reloc,
			bool autostart,
			int router_chans)
{
	int status = 0;
	unsigned int sample_rate;
	unsigned short channels;

	codec_dbg(codec, "---- dspload_image begin ------\n");
	if (router_chans == 0) {
		if (!ovly)
			router_chans = DMA_TRANSFER_FRAME_SIZE_NWORDS;
		else
			router_chans = DMA_OVERLAY_FRAME_SIZE_NWORDS;
	}

	sample_rate = 48000;
	channels = (unsigned short)router_chans;

	while (channels > 16) {
		sample_rate *= 2;
		channels /= 2;
	}

	do {
		codec_dbg(codec, "Ready to program DMA\n");
		if (!ovly)
			status = dsp_reset(codec);

		if (status < 0)
			break;

		codec_dbg(codec, "dsp_reset() complete\n");
		status = dspxfr_image(codec, fls, reloc, sample_rate, channels,
				      ovly);

		if (status < 0)
			break;

		codec_dbg(codec, "dspxfr_image() complete\n");
		if (autostart && !ovly) {
			dspload_post_setup(codec);
			status = dsp_set_run_state(codec);
		}

		codec_dbg(codec, "LOAD FINISHED\n");
	} while (0);

	return status;
}