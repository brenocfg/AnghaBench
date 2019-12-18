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
typedef  unsigned long long u64 ;
struct uac_format_type_i_ext_descriptor {int bBitResolution; int bSubslotSize; } ;
struct uac_format_type_i_discrete_descriptor {int bBitResolution; int bSubframeSize; } ;
struct uac3_as_header_descriptor {int bBitResolution; int bSubslotSize; } ;
struct snd_usb_audio {scalar_t__ usb_id; } ;
struct audioformat {int protocol; int dsd_raw; int fmt_bits; int /*<<< orphan*/  altsetting; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 unsigned long long SNDRV_PCM_FMTBIT_A_LAW ; 
 unsigned long long SNDRV_PCM_FMTBIT_FLOAT_LE ; 
 unsigned long long SNDRV_PCM_FMTBIT_MU_LAW ; 
 unsigned long long SNDRV_PCM_FMTBIT_S16_BE ; 
 unsigned long long SNDRV_PCM_FMTBIT_S16_LE ; 
 unsigned long long SNDRV_PCM_FMTBIT_S24_3BE ; 
 unsigned long long SNDRV_PCM_FMTBIT_S24_3LE ; 
 unsigned long long SNDRV_PCM_FMTBIT_S32_LE ; 
 unsigned long long SNDRV_PCM_FMTBIT_S8 ; 
 unsigned long long SNDRV_PCM_FMTBIT_SPECIAL ; 
 unsigned long long SNDRV_PCM_FMTBIT_U8 ; 
 unsigned long long UAC2_FORMAT_TYPE_I_RAW_DATA ; 
 unsigned long long UAC3_FORMAT_TYPE_I_RAW_DATA ; 
 int UAC_FORMAT_TYPE_I_ALAW ; 
 int UAC_FORMAT_TYPE_I_IEEE_FLOAT ; 
 int UAC_FORMAT_TYPE_I_MULAW ; 
 int UAC_FORMAT_TYPE_I_PCM ; 
 int UAC_FORMAT_TYPE_I_PCM8 ; 
 int UAC_FORMAT_TYPE_I_UNDEFINED ; 
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 
 scalar_t__ USB_ID (int,int) ; 
 unsigned long long snd_usb_interface_dsd_format_quirks (struct snd_usb_audio*,struct audioformat*,int) ; 
 int /*<<< orphan*/  snd_usb_is_big_endian_format (struct snd_usb_audio*,struct audioformat*) ; 
 int /*<<< orphan*/  usb_audio_info (struct snd_usb_audio*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static u64 parse_audio_format_i_type(struct snd_usb_audio *chip,
				     struct audioformat *fp,
				     u64 format, void *_fmt)
{
	int sample_width, sample_bytes;
	u64 pcm_formats = 0;

	switch (fp->protocol) {
	case UAC_VERSION_1:
	default: {
		struct uac_format_type_i_discrete_descriptor *fmt = _fmt;
		sample_width = fmt->bBitResolution;
		sample_bytes = fmt->bSubframeSize;
		format = 1ULL << format;
		break;
	}

	case UAC_VERSION_2: {
		struct uac_format_type_i_ext_descriptor *fmt = _fmt;
		sample_width = fmt->bBitResolution;
		sample_bytes = fmt->bSubslotSize;

		if (format & UAC2_FORMAT_TYPE_I_RAW_DATA) {
			pcm_formats |= SNDRV_PCM_FMTBIT_SPECIAL;
			/* flag potentially raw DSD capable altsettings */
			fp->dsd_raw = true;
		}

		format <<= 1;
		break;
	}
	case UAC_VERSION_3: {
		struct uac3_as_header_descriptor *as = _fmt;

		sample_width = as->bBitResolution;
		sample_bytes = as->bSubslotSize;

		if (format & UAC3_FORMAT_TYPE_I_RAW_DATA)
			pcm_formats |= SNDRV_PCM_FMTBIT_SPECIAL;

		format <<= 1;
		break;
	}
	}

	fp->fmt_bits = sample_width;

	if ((pcm_formats == 0) &&
	    (format == 0 || format == (1 << UAC_FORMAT_TYPE_I_UNDEFINED))) {
		/* some devices don't define this correctly... */
		usb_audio_info(chip, "%u:%d : format type 0 is detected, processed as PCM\n",
			fp->iface, fp->altsetting);
		format = 1 << UAC_FORMAT_TYPE_I_PCM;
	}
	if (format & (1 << UAC_FORMAT_TYPE_I_PCM)) {
		if (((chip->usb_id == USB_ID(0x0582, 0x0016)) ||
		     /* Edirol SD-90 */
		     (chip->usb_id == USB_ID(0x0582, 0x000c))) &&
		     /* Roland SC-D70 */
		    sample_width == 24 && sample_bytes == 2)
			sample_bytes = 3;
		else if (sample_width > sample_bytes * 8) {
			usb_audio_info(chip, "%u:%d : sample bitwidth %d in over sample bytes %d\n",
				 fp->iface, fp->altsetting,
				 sample_width, sample_bytes);
		}
		/* check the format byte size */
		switch (sample_bytes) {
		case 1:
			pcm_formats |= SNDRV_PCM_FMTBIT_S8;
			break;
		case 2:
			if (snd_usb_is_big_endian_format(chip, fp))
				pcm_formats |= SNDRV_PCM_FMTBIT_S16_BE; /* grrr, big endian!! */
			else
				pcm_formats |= SNDRV_PCM_FMTBIT_S16_LE;
			break;
		case 3:
			if (snd_usb_is_big_endian_format(chip, fp))
				pcm_formats |= SNDRV_PCM_FMTBIT_S24_3BE; /* grrr, big endian!! */
			else
				pcm_formats |= SNDRV_PCM_FMTBIT_S24_3LE;
			break;
		case 4:
			pcm_formats |= SNDRV_PCM_FMTBIT_S32_LE;
			break;
		default:
			usb_audio_info(chip,
				 "%u:%d : unsupported sample bitwidth %d in %d bytes\n",
				 fp->iface, fp->altsetting,
				 sample_width, sample_bytes);
			break;
		}
	}
	if (format & (1 << UAC_FORMAT_TYPE_I_PCM8)) {
		/* Dallas DS4201 workaround: it advertises U8 format, but really
		   supports S8. */
		if (chip->usb_id == USB_ID(0x04fa, 0x4201))
			pcm_formats |= SNDRV_PCM_FMTBIT_S8;
		else
			pcm_formats |= SNDRV_PCM_FMTBIT_U8;
	}
	if (format & (1 << UAC_FORMAT_TYPE_I_IEEE_FLOAT)) {
		pcm_formats |= SNDRV_PCM_FMTBIT_FLOAT_LE;
	}
	if (format & (1 << UAC_FORMAT_TYPE_I_ALAW)) {
		pcm_formats |= SNDRV_PCM_FMTBIT_A_LAW;
	}
	if (format & (1 << UAC_FORMAT_TYPE_I_MULAW)) {
		pcm_formats |= SNDRV_PCM_FMTBIT_MU_LAW;
	}
	if (format & ~0x3f) {
		usb_audio_info(chip,
			 "%u:%d : unsupported format bits %#llx\n",
			 fp->iface, fp->altsetting, format);
	}

	pcm_formats |= snd_usb_interface_dsd_format_quirks(chip, fp, sample_bytes);

	return pcm_formats;
}