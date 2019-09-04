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

/* Variables and functions */
 scalar_t__ USB_EXT_PROP_B_PROPERTY_DATA ; 
 int /*<<< orphan*/ * __usb_ext_prop_ptr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline u8 *usb_ext_prop_data_ptr(u8 *buf, size_t off)
{
	return __usb_ext_prop_ptr(buf, USB_EXT_PROP_B_PROPERTY_DATA + off);
}