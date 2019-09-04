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
struct ep_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ep_device*) ; 
 struct ep_device* to_ep_device (struct device*) ; 

__attribute__((used)) static void ep_device_release(struct device *dev)
{
	struct ep_device *ep_dev = to_ep_device(dev);

	kfree(ep_dev);
}