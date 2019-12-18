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
typedef  int /*<<< orphan*/  u64 ;
struct uac_format_type_i_continuous_descriptor {int bFormatType; } ;
struct snd_usb_audio {scalar_t__ usb_id; } ;
struct audioformat {int fmt_type; scalar_t__ rates; int /*<<< orphan*/  altsetting; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ SNDRV_PCM_RATE_48000 ; 
 scalar_t__ SNDRV_PCM_RATE_96000 ; 
#define  UAC_FORMAT_TYPE_I 130 
#define  UAC_FORMAT_TYPE_II 129 
#define  UAC_FORMAT_TYPE_III 128 
 scalar_t__ USB_ID (int,int) ; 
 int parse_audio_format_i (struct snd_usb_audio*,struct audioformat*,int /*<<< orphan*/ ,struct uac_format_type_i_continuous_descriptor*) ; 
 int parse_audio_format_ii (struct snd_usb_audio*,struct audioformat*,int /*<<< orphan*/ ,struct uac_format_type_i_continuous_descriptor*) ; 
 int /*<<< orphan*/  usb_audio_info (struct snd_usb_audio*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_usb_parse_audio_format(struct snd_usb_audio *chip,
			       struct audioformat *fp, u64 format,
			       struct uac_format_type_i_continuous_descriptor *fmt,
			       int stream)
{
	int err;

	switch (fmt->bFormatType) {
	case UAC_FORMAT_TYPE_I:
	case UAC_FORMAT_TYPE_III:
		err = parse_audio_format_i(chip, fp, format, fmt);
		break;
	case UAC_FORMAT_TYPE_II:
		err = parse_audio_format_ii(chip, fp, format, fmt);
		break;
	default:
		usb_audio_info(chip,
			 "%u:%d : format type %d is not supported yet\n",
			 fp->iface, fp->altsetting,
			 fmt->bFormatType);
		return -ENOTSUPP;
	}
	fp->fmt_type = fmt->bFormatType;
	if (err < 0)
		return err;
#if 1
	/* FIXME: temporary hack for extigy/audigy 2 nx/zs */
	/* extigy apparently supports sample rates other than 48k
	 * but not in ordinary way.  so we enable only 48k atm.
	 */
	if (chip->usb_id == USB_ID(0x041e, 0x3000) ||
	    chip->usb_id == USB_ID(0x041e, 0x3020) ||
	    chip->usb_id == USB_ID(0x041e, 0x3061)) {
		if (fmt->bFormatType == UAC_FORMAT_TYPE_I &&
		    fp->rates != SNDRV_PCM_RATE_48000 &&
		    fp->rates != SNDRV_PCM_RATE_96000)
			return -ENOTSUPP;
	}
#endif
	return 0;
}