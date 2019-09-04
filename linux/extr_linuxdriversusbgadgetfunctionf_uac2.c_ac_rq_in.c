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
struct usb_function {int dummy; } ;
struct usb_ctrlrequest {scalar_t__ bRequest; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ UAC2_CS_CUR ; 
 scalar_t__ UAC2_CS_RANGE ; 
 int in_rq_cur (struct usb_function*,struct usb_ctrlrequest const*) ; 
 int in_rq_range (struct usb_function*,struct usb_ctrlrequest const*) ; 

__attribute__((used)) static int
ac_rq_in(struct usb_function *fn, const struct usb_ctrlrequest *cr)
{
	if (cr->bRequest == UAC2_CS_CUR)
		return in_rq_cur(fn, cr);
	else if (cr->bRequest == UAC2_CS_RANGE)
		return in_rq_range(fn, cr);
	else
		return -EOPNOTSUPP;
}