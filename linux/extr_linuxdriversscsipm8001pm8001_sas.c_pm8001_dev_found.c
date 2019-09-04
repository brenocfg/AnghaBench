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
struct domain_device {int dummy; } ;

/* Variables and functions */
 int pm8001_dev_found_notify (struct domain_device*) ; 

int pm8001_dev_found(struct domain_device *dev)
{
	return pm8001_dev_found_notify(dev);
}