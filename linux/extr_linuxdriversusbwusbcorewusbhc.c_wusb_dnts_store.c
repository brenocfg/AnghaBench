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
typedef  void* uint8_t ;
struct wusbhc {void* dnts_interval; void* dnts_num_slots; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int sscanf (char const*,char*,void**,void**) ; 
 struct wusbhc* usbhc_dev_to_wusbhc (struct device*) ; 

__attribute__((used)) static ssize_t wusb_dnts_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t size)
{
	struct wusbhc *wusbhc = usbhc_dev_to_wusbhc(dev);
	uint8_t num_slots, interval;
	ssize_t result;

	result = sscanf(buf, "%hhu %hhu", &num_slots, &interval);

	if (result != 2)
		return -EINVAL;

	wusbhc->dnts_num_slots = num_slots;
	wusbhc->dnts_interval = interval;

	return size;
}