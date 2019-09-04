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
struct usb_host_interface {int dummy; } ;
struct snd_usb_audio {int /*<<< orphan*/  badd_profile; } ;
struct audioformat {int protocol; } ;

/* Variables and functions */
 int ENXIO ; 
 int UAC3_BADD_SAMPLING_RATE ; 
 int /*<<< orphan*/  UAC3_FUNCTION_SUBCLASS_GENERIC_IO ; 
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 
 int set_sample_rate_v1 (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*,int) ; 
 int set_sample_rate_v2v3 (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*,int) ; 

int snd_usb_init_sample_rate(struct snd_usb_audio *chip, int iface,
			     struct usb_host_interface *alts,
			     struct audioformat *fmt, int rate)
{
	switch (fmt->protocol) {
	case UAC_VERSION_1:
	default:
		return set_sample_rate_v1(chip, iface, alts, fmt, rate);

	case UAC_VERSION_3:
		if (chip->badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) {
			if (rate != UAC3_BADD_SAMPLING_RATE)
				return -ENXIO;
			else
				return 0;
		}
	/* fall through */
	case UAC_VERSION_2:
		return set_sample_rate_v2v3(chip, iface, alts, fmt, rate);
	}
}