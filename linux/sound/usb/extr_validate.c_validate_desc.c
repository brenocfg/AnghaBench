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
struct usb_desc_validator {char type; int protocol; int (* func ) (unsigned char*,struct usb_desc_validator const*) ;unsigned char size; } ;

/* Variables and functions */
 int UAC_VERSION_ALL ; 
 unsigned char USB_DT_CS_INTERFACE ; 
 int stub1 (unsigned char*,struct usb_desc_validator const*) ; 

__attribute__((used)) static bool validate_desc(unsigned char *hdr, int protocol,
			  const struct usb_desc_validator *v)
{
	if (hdr[1] != USB_DT_CS_INTERFACE)
		return true; /* don't care */

	for (; v->type; v++) {
		if (v->type == hdr[2] &&
		    (v->protocol == UAC_VERSION_ALL ||
		     v->protocol == protocol)) {
			if (v->func)
				return v->func(hdr, v);
			/* check for the fixed size */
			return hdr[0] >= v->size;
		}
	}

	return true; /* not matching, skip validation */
}