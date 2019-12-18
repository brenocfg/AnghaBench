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
typedef  int u64 ;
struct uac_format_type_ii_ext_descriptor {int /*<<< orphan*/  wSamplesPerFrame; int /*<<< orphan*/  wMaxBitRate; } ;
struct uac_format_type_ii_discrete_descriptor {int /*<<< orphan*/  wSamplesPerFrame; int /*<<< orphan*/  wMaxBitRate; } ;
struct snd_usb_audio {int dummy; } ;
struct audioformat {int channels; int protocol; int frame_size; void* formats; int /*<<< orphan*/  altsetting; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 void* SNDRV_PCM_FMTBIT_MPEG ; 
 void* SNDRV_PCM_FMTBIT_U8 ; 
#define  UAC_FORMAT_TYPE_II_AC3 131 
#define  UAC_FORMAT_TYPE_II_MPEG 130 
#define  UAC_VERSION_1 129 
#define  UAC_VERSION_2 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_audio_format_rates_v1 (struct snd_usb_audio*,struct audioformat*,void*,int) ; 
 int parse_audio_format_rates_v2v3 (struct snd_usb_audio*,struct audioformat*) ; 
 int /*<<< orphan*/  usb_audio_info (struct snd_usb_audio*,char*,int,int,...) ; 

__attribute__((used)) static int parse_audio_format_ii(struct snd_usb_audio *chip,
				 struct audioformat *fp,
				 u64 format, void *_fmt)
{
	int brate, framesize, ret;

	switch (format) {
	case UAC_FORMAT_TYPE_II_AC3:
		/* FIXME: there is no AC3 format defined yet */
		// fp->formats = SNDRV_PCM_FMTBIT_AC3;
		fp->formats = SNDRV_PCM_FMTBIT_U8; /* temporary hack to receive byte streams */
		break;
	case UAC_FORMAT_TYPE_II_MPEG:
		fp->formats = SNDRV_PCM_FMTBIT_MPEG;
		break;
	default:
		usb_audio_info(chip,
			 "%u:%d : unknown format tag %#llx is detected.  processed as MPEG.\n",
			 fp->iface, fp->altsetting, format);
		fp->formats = SNDRV_PCM_FMTBIT_MPEG;
		break;
	}

	fp->channels = 1;

	switch (fp->protocol) {
	default:
	case UAC_VERSION_1: {
		struct uac_format_type_ii_discrete_descriptor *fmt = _fmt;
		brate = le16_to_cpu(fmt->wMaxBitRate);
		framesize = le16_to_cpu(fmt->wSamplesPerFrame);
		usb_audio_info(chip, "found format II with max.bitrate = %d, frame size=%d\n", brate, framesize);
		fp->frame_size = framesize;
		ret = parse_audio_format_rates_v1(chip, fp, _fmt, 8); /* fmt[8..] sample rates */
		break;
	}
	case UAC_VERSION_2: {
		struct uac_format_type_ii_ext_descriptor *fmt = _fmt;
		brate = le16_to_cpu(fmt->wMaxBitRate);
		framesize = le16_to_cpu(fmt->wSamplesPerFrame);
		usb_audio_info(chip, "found format II with max.bitrate = %d, frame size=%d\n", brate, framesize);
		fp->frame_size = framesize;
		ret = parse_audio_format_rates_v2v3(chip, fp);
		break;
	}
	}

	return ret;
}