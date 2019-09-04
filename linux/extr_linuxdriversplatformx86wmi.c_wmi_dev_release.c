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
struct wmi_block {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct wmi_block* dev_to_wblock (struct device*) ; 
 int /*<<< orphan*/  kfree (struct wmi_block*) ; 

__attribute__((used)) static void wmi_dev_release(struct device *dev)
{
	struct wmi_block *wblock = dev_to_wblock(dev);

	kfree(wblock);
}