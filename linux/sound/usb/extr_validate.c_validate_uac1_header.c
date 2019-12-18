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
struct usb_desc_validator {int dummy; } ;
struct uac1_ac_header_descriptor {int bLength; int bInCollection; } ;

/* Variables and functions */

__attribute__((used)) static bool validate_uac1_header(const void *p,
				 const struct usb_desc_validator *v)
{
	const struct uac1_ac_header_descriptor *d = p;

	return d->bLength >= sizeof(*d) &&
		d->bLength >= sizeof(*d) + d->bInCollection;
}