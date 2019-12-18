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
struct snd_usb_endpoint {scalar_t__ use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int) ; 
 int /*<<< orphan*/  wait_clear_urbs (struct snd_usb_endpoint*) ; 

void snd_usb_endpoint_deactivate(struct snd_usb_endpoint *ep)
{
	if (!ep)
		return;

	if (ep->use_count != 0)
		return;

	deactivate_urbs(ep, true);
	wait_clear_urbs(ep);
}