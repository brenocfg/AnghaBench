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
struct snd_usb_audio {int dummy; } ;

/* Variables and functions */
 int __snd_usb_parse_audio_interface (struct snd_usb_audio*,int,int*,int) ; 

int snd_usb_parse_audio_interface(struct snd_usb_audio *chip, int iface_no)
{
	int err;
	bool has_non_pcm = false;

	/* parse PCM formats */
	err = __snd_usb_parse_audio_interface(chip, iface_no, &has_non_pcm, false);
	if (err < 0)
		return err;

	if (has_non_pcm) {
		/* parse non-PCM formats */
		err = __snd_usb_parse_audio_interface(chip, iface_no, &has_non_pcm, true);
		if (err < 0)
			return err;
	}

	return 0;
}