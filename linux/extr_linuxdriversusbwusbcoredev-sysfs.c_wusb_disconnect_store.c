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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int /*<<< orphan*/  mutex; } ;
struct usb_device {int /*<<< orphan*/  portnum; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int /*<<< orphan*/  __wusbhc_dev_disable (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int /*<<< orphan*/  wusb_port_no_to_idx (int /*<<< orphan*/ ) ; 
 struct wusbhc* wusbhc_get_by_usb_dev (struct usb_device*) ; 
 int /*<<< orphan*/  wusbhc_put (struct wusbhc*) ; 

__attribute__((used)) static ssize_t wusb_disconnect_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t size)
{
	struct usb_device *usb_dev;
	struct wusbhc *wusbhc;
	unsigned command;
	u8 port_idx;

	if (sscanf(buf, "%u", &command) != 1)
		return -EINVAL;
	if (command == 0)
		return size;
	usb_dev = to_usb_device(dev);
	wusbhc = wusbhc_get_by_usb_dev(usb_dev);
	if (wusbhc == NULL)
		return -ENODEV;

	mutex_lock(&wusbhc->mutex);
	port_idx = wusb_port_no_to_idx(usb_dev->portnum);
	__wusbhc_dev_disable(wusbhc, port_idx);
	mutex_unlock(&wusbhc->mutex);
	wusbhc_put(wusbhc);
	return size;
}