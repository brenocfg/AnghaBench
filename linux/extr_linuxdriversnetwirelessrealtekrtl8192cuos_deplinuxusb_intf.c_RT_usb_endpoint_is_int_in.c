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
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
 scalar_t__ RT_usb_endpoint_dir_in (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ RT_usb_endpoint_xfer_int (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static inline int RT_usb_endpoint_is_int_in(const struct usb_endpoint_descriptor *epd)
{
	return (RT_usb_endpoint_xfer_int(epd) && RT_usb_endpoint_dir_in(epd));
}