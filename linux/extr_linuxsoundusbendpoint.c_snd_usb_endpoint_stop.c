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
struct snd_usb_endpoint {scalar_t__ use_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FLAG_STOPPING ; 
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

void snd_usb_endpoint_stop(struct snd_usb_endpoint *ep)
{
	if (!ep)
		return;

	if (snd_BUG_ON(ep->use_count == 0))
		return;

	if (--ep->use_count == 0) {
		deactivate_urbs(ep, false);
		set_bit(EP_FLAG_STOPPING, &ep->flags);
	}
}