#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bInterfaceSubClass; int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_endpoint_is_int_in (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hub_descriptor_is_sane(struct usb_host_interface *desc)
{
	/* Some hubs have a subclass of 1, which AFAICT according to the */
	/*  specs is not defined, but it works */
	if (desc->desc.bInterfaceSubClass != 0 &&
	    desc->desc.bInterfaceSubClass != 1)
		return false;

	/* Multiple endpoints? What kind of mutant ninja-hub is this? */
	if (desc->desc.bNumEndpoints != 1)
		return false;

	/* If the first endpoint is not interrupt IN, we'd better punt! */
	if (!usb_endpoint_is_int_in(&desc->endpoint[0].desc))
		return false;

        return true;
}