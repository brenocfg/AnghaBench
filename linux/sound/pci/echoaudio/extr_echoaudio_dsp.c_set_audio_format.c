#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct echoaudio {TYPE_2__* comm_page; TYPE_1__* card; } ;
struct audioformat {int interleave; int bits_per_sample; int /*<<< orphan*/  mono_to_stereo; scalar_t__ data_are_bigendian; } ;
struct TYPE_4__ {int /*<<< orphan*/ * audio_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DSP_AUDIOFORM_MM_32BE ; 
 size_t DSP_AUDIOFORM_MM_32LE ; 
 size_t DSP_AUDIOFORM_MS_16LE ; 
 size_t DSP_AUDIOFORM_MS_24LE ; 
 size_t DSP_AUDIOFORM_MS_32LE ; 
 size_t DSP_AUDIOFORM_MS_8 ; 
 size_t DSP_AUDIOFORM_SS_16LE ; 
 size_t DSP_AUDIOFORM_SS_24LE ; 
 size_t DSP_AUDIOFORM_SS_32BE ; 
 size_t DSP_AUDIOFORM_SS_32LE ; 
 size_t DSP_AUDIOFORM_SS_8 ; 
 size_t DSP_AUDIOFORM_SUPER_INTERLEAVE_16LE ; 
 size_t DSP_AUDIOFORM_SUPER_INTERLEAVE_24LE ; 
 size_t DSP_AUDIOFORM_SUPER_INTERLEAVE_32LE ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static void set_audio_format(struct echoaudio *chip, u16 pipe_index,
			     const struct audioformat *format)
{
	u16 dsp_format;

	dsp_format = DSP_AUDIOFORM_SS_16LE;

	/* Look for super-interleave (no big-endian and 8 bits) */
	if (format->interleave > 2) {
		switch (format->bits_per_sample) {
		case 16:
			dsp_format = DSP_AUDIOFORM_SUPER_INTERLEAVE_16LE;
			break;
		case 24:
			dsp_format = DSP_AUDIOFORM_SUPER_INTERLEAVE_24LE;
			break;
		case 32:
			dsp_format = DSP_AUDIOFORM_SUPER_INTERLEAVE_32LE;
			break;
		}
		dsp_format |= format->interleave;
	} else if (format->data_are_bigendian) {
		/* For big-endian data, only 32 bit samples are supported */
		switch (format->interleave) {
		case 1:
			dsp_format = DSP_AUDIOFORM_MM_32BE;
			break;
#ifdef ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		case 2:
			dsp_format = DSP_AUDIOFORM_SS_32BE;
			break;
#endif
		}
	} else if (format->interleave == 1 &&
		   format->bits_per_sample == 32 && !format->mono_to_stereo) {
		/* 32 bit little-endian mono->mono case */
		dsp_format = DSP_AUDIOFORM_MM_32LE;
	} else {
		/* Handle the other little-endian formats */
		switch (format->bits_per_sample) {
		case 8:
			if (format->interleave == 2)
				dsp_format = DSP_AUDIOFORM_SS_8;
			else
				dsp_format = DSP_AUDIOFORM_MS_8;
			break;
		default:
		case 16:
			if (format->interleave == 2)
				dsp_format = DSP_AUDIOFORM_SS_16LE;
			else
				dsp_format = DSP_AUDIOFORM_MS_16LE;
			break;
		case 24:
			if (format->interleave == 2)
				dsp_format = DSP_AUDIOFORM_SS_24LE;
			else
				dsp_format = DSP_AUDIOFORM_MS_24LE;
			break;
		case 32:
			if (format->interleave == 2)
				dsp_format = DSP_AUDIOFORM_SS_32LE;
			else
				dsp_format = DSP_AUDIOFORM_MS_32LE;
			break;
		}
	}
	dev_dbg(chip->card->dev,
		 "set_audio_format[%d] = %x\n", pipe_index, dsp_format);
	chip->comm_page->audio_format[pipe_index] = cpu_to_le16(dsp_format);
}