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
struct usb_ep {int dummy; } ;
struct s3c_hsudc_ep {int wedge; } ;

/* Variables and functions */
 int EINVAL ; 
 struct s3c_hsudc_ep* our_ep (struct usb_ep*) ; 
 int usb_ep_set_halt (struct usb_ep*) ; 

__attribute__((used)) static int s3c_hsudc_set_wedge(struct usb_ep *_ep)
{
	struct s3c_hsudc_ep *hsep = our_ep(_ep);

	if (!hsep)
		return -EINVAL;

	hsep->wedge = 1;
	return usb_ep_set_halt(_ep);
}