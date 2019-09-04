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
struct snd_usb_endpoint {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FLAG_STOPPING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_clear_urbs (struct snd_usb_endpoint*) ; 

void snd_usb_endpoint_sync_pending_stop(struct snd_usb_endpoint *ep)
{
	if (ep && test_bit(EP_FLAG_STOPPING, &ep->flags))
		wait_clear_urbs(ep);
}