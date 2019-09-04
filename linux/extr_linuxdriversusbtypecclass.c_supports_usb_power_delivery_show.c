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
struct typec_partner {scalar_t__ usb_pd; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct typec_partner* to_typec_partner (struct device*) ; 

__attribute__((used)) static ssize_t supports_usb_power_delivery_show(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct typec_partner *p = to_typec_partner(dev);

	return sprintf(buf, "%s\n", p->usb_pd ? "yes" : "no");
}