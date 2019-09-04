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
struct wusbhc {int /*<<< orphan*/  mutex; struct device* dev; } ;
struct wusb_dev {int /*<<< orphan*/  port_idx; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wusbhc_dev_disconnect (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusb_port_by_idx (struct wusbhc*,int /*<<< orphan*/ ) ; 
 struct wusb_dev* wusbhc_find_dev_by_addr (struct wusbhc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wusbhc_handle_dn_disconnect(struct wusbhc *wusbhc, u8 srcaddr)
{
	struct device *dev = wusbhc->dev;
	struct wusb_dev *wusb_dev;

	mutex_lock(&wusbhc->mutex);
	wusb_dev = wusbhc_find_dev_by_addr(wusbhc, srcaddr);
	if (wusb_dev == NULL) {
		dev_dbg(dev, "ignoring DN DISCONNECT from unconnected device %02x\n",
			srcaddr);
	} else {
		dev_info(dev, "DN DISCONNECT: device 0x%02x going down\n",
			wusb_dev->addr);
		__wusbhc_dev_disconnect(wusbhc, wusb_port_by_idx(wusbhc,
			wusb_dev->port_idx));
	}
	mutex_unlock(&wusbhc->mutex);
}