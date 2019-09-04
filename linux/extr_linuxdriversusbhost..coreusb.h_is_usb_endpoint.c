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
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_ep_device_type ; 

__attribute__((used)) static inline int is_usb_endpoint(const struct device *dev)
{
	return dev->type == &usb_ep_device_type;
}