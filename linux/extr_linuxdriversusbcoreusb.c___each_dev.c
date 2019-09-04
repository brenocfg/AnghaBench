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
struct each_dev_arg {int (* fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_usb_device (struct device*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 

__attribute__((used)) static int __each_dev(struct device *dev, void *data)
{
	struct each_dev_arg *arg = (struct each_dev_arg *)data;

	/* There are struct usb_interface on the same bus, filter them out */
	if (!is_usb_device(dev))
		return 0;

	return arg->fn(to_usb_device(dev), arg->data);
}