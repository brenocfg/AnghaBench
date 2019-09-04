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
struct snd_usb_audio {scalar_t__ usb_id; } ;
struct audioformat {int altsetting; unsigned int* rate_table; size_t nr_rates; unsigned int rate_min; unsigned int rate_max; int maxpacksize; int /*<<< orphan*/  rates; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_CONTINUOUS ; 
 scalar_t__ USB_ID (int,int) ; 
 void* combine_triple (unsigned char*) ; 
 int /*<<< orphan*/  hwc_debug (char*) ; 
 unsigned int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (unsigned int) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_audio_format_rates_v1(struct snd_usb_audio *chip, struct audioformat *fp,
				       unsigned char *fmt, int offset)
{
	int nr_rates = fmt[offset];

	if (fmt[0] < offset + 1 + 3 * (nr_rates ? nr_rates : 2)) {
		usb_audio_err(chip,
			"%u:%d : invalid UAC_FORMAT_TYPE desc\n",
			fp->iface, fp->altsetting);
		return -EINVAL;
	}

	if (nr_rates) {
		/*
		 * build the rate table and bitmap flags
		 */
		int r, idx;

		fp->rate_table = kmalloc_array(nr_rates, sizeof(int),
					       GFP_KERNEL);
		if (fp->rate_table == NULL)
			return -ENOMEM;

		fp->nr_rates = 0;
		fp->rate_min = fp->rate_max = 0;
		for (r = 0, idx = offset + 1; r < nr_rates; r++, idx += 3) {
			unsigned int rate = combine_triple(&fmt[idx]);
			if (!rate)
				continue;
			/* C-Media CM6501 mislabels its 96 kHz altsetting */
			/* Terratec Aureon 7.1 USB C-Media 6206, too */
			if (rate == 48000 && nr_rates == 1 &&
			    (chip->usb_id == USB_ID(0x0d8c, 0x0201) ||
			     chip->usb_id == USB_ID(0x0d8c, 0x0102) ||
			     chip->usb_id == USB_ID(0x0ccd, 0x00b1)) &&
			    fp->altsetting == 5 && fp->maxpacksize == 392)
				rate = 96000;
			/* Creative VF0420/VF0470 Live Cams report 16 kHz instead of 8kHz */
			if (rate == 16000 &&
			    (chip->usb_id == USB_ID(0x041e, 0x4064) ||
			     chip->usb_id == USB_ID(0x041e, 0x4068)))
				rate = 8000;

			fp->rate_table[fp->nr_rates] = rate;
			if (!fp->rate_min || rate < fp->rate_min)
				fp->rate_min = rate;
			if (!fp->rate_max || rate > fp->rate_max)
				fp->rate_max = rate;
			fp->rates |= snd_pcm_rate_to_rate_bit(rate);
			fp->nr_rates++;
		}
		if (!fp->nr_rates) {
			hwc_debug("All rates were zero. Skipping format!\n");
			return -EINVAL;
		}
	} else {
		/* continuous rates */
		fp->rates = SNDRV_PCM_RATE_CONTINUOUS;
		fp->rate_min = combine_triple(&fmt[offset + 1]);
		fp->rate_max = combine_triple(&fmt[offset + 4]);
	}
	return 0;
}