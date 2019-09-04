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
struct wlcore_platdev_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 

__attribute__((used)) static int wlcore_probe_of(struct device *dev, int *irq,
			   struct wlcore_platdev_data *pdev_data)
{
	return -ENODATA;
}