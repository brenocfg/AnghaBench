#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct brcmf_usbdev_info {int dummy; } ;
struct TYPE_2__ {struct brcmf_usbdev_info* devinfo; } ;

/* Variables and functions */
 TYPE_1__* brcmf_usb_get_buspub (struct device*) ; 

__attribute__((used)) static struct brcmf_usbdev_info *brcmf_usb_get_businfo(struct device *dev)
{
	return brcmf_usb_get_buspub(dev)->devinfo;
}