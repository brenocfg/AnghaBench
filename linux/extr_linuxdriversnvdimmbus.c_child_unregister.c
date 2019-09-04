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
struct device {scalar_t__ class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_SYNC ; 
 int /*<<< orphan*/  nd_device_unregister (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int child_unregister(struct device *dev, void *data)
{
	/*
	 * the singular ndctl class device per bus needs to be
	 * "device_destroy"ed, so skip it here
	 *
	 * i.e. remove classless children
	 */
	if (dev->class)
		/* pass */;
	else
		nd_device_unregister(dev, ND_SYNC);
	return 0;
}