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
struct wusbhc {int phy_rate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct wusbhc* usbhc_dev_to_wusbhc (struct device*) ; 

__attribute__((used)) static ssize_t wusb_phy_rate_show(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	struct wusbhc *wusbhc = usbhc_dev_to_wusbhc(dev);

	return sprintf(buf, "%d\n", wusbhc->phy_rate);
}