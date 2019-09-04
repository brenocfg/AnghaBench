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
typedef  int u8 ;
struct wusbhc {int (* dev_info_set ) (struct wusbhc*,struct wusb_dev*) ;int /*<<< orphan*/  dev; } ;
struct wusb_dev {int addr; int /*<<< orphan*/  port_idx; } ;

/* Variables and functions */
 int WUSB_DEV_ADDR_UNAUTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct wusbhc*,struct wusb_dev*) ; 

int wusb_set_dev_addr(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev, u8 addr)
{
	int result;

	wusb_dev->addr = addr;
	result = wusbhc->dev_info_set(wusbhc, wusb_dev);
	if (result < 0)
		dev_err(wusbhc->dev, "device %d: failed to set device "
			"address\n", wusb_dev->port_idx);
	else
		dev_info(wusbhc->dev, "device %d: %s addr %u\n",
			 wusb_dev->port_idx,
			 (addr & WUSB_DEV_ADDR_UNAUTH) ? "unauth" : "auth",
			 wusb_dev->addr);

	return result;
}