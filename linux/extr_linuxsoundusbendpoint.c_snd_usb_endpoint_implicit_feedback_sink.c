#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_endpoint {scalar_t__ type; int /*<<< orphan*/  pipe; TYPE_1__* sync_master; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SND_USB_ENDPOINT_TYPE_DATA ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 

int snd_usb_endpoint_implicit_feedback_sink(struct snd_usb_endpoint *ep)
{
	return  ep->sync_master &&
		ep->sync_master->type == SND_USB_ENDPOINT_TYPE_DATA &&
		ep->type == SND_USB_ENDPOINT_TYPE_DATA &&
		usb_pipeout(ep->pipe);
}