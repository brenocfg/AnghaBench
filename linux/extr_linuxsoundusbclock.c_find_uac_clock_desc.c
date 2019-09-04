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
typedef  int /*<<< orphan*/  u8 ;
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;

/* Variables and functions */
 void* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *find_uac_clock_desc(struct usb_host_interface *iface, int id,
				 bool (*validator)(void *, int), u8 type)
{
	void *cs = NULL;

	while ((cs = snd_usb_find_csint_desc(iface->extra, iface->extralen,
					     cs, type))) {
		if (validator(cs, id))
			return cs;
	}

	return NULL;
}