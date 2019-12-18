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
struct usb_midi_out_jack_descriptor {int bLength; int bNrInputPins; } ;
struct usb_desc_validator {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool validate_midi_out_jack(const void *p,
				   const struct usb_desc_validator *v)
{
	const struct usb_midi_out_jack_descriptor *d = p;

	return d->bLength >= sizeof(*d) &&
		d->bLength >= sizeof(*d) + d->bNrInputPins * 2;
}