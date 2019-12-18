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
struct usb_desc_validator {int protocol; } ;
struct uac_mixer_unit_descriptor {int bLength; int bNrInPins; } ;

/* Variables and functions */
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 

__attribute__((used)) static bool validate_mixer_unit(const void *p,
				const struct usb_desc_validator *v)
{
	const struct uac_mixer_unit_descriptor *d = p;
	size_t len;

	if (d->bLength < sizeof(*d) || !d->bNrInPins)
		return false;
	len = sizeof(*d) + d->bNrInPins;
	/* We can't determine the bitmap size only from this unit descriptor,
	 * so just check with the remaining length.
	 * The actual bitmap is checked at mixer unit parser.
	 */
	switch (v->protocol) {
	case UAC_VERSION_1:
	default:
		len += 2 + 1; /* wChannelConfig, iChannelNames */
		/* bmControls[n*m] */
		len += 1; /* iMixer */
		break;
	case UAC_VERSION_2:
		len += 4 + 1; /* bmChannelConfig, iChannelNames */
		/* bmMixerControls[n*m] */
		len += 1 + 1; /* bmControls, iMixer */
		break;
	case UAC_VERSION_3:
		len += 2; /* wClusterDescrID */
		/* bmMixerControls[n*m] */
		break;
	}
	return d->bLength >= len;
}