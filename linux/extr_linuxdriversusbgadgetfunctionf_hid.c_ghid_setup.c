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
struct usb_gadget {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hidg_class ; 
 int /*<<< orphan*/  major ; 
 int minors ; 

int ghid_setup(struct usb_gadget *g, int count)
{
	int status;
	dev_t dev;

	hidg_class = class_create(THIS_MODULE, "hidg");
	if (IS_ERR(hidg_class)) {
		status = PTR_ERR(hidg_class);
		hidg_class = NULL;
		return status;
	}

	status = alloc_chrdev_region(&dev, 0, count, "hidg");
	if (status) {
		class_destroy(hidg_class);
		hidg_class = NULL;
		return status;
	}

	major = MAJOR(dev);
	minors = count;

	return 0;
}