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
struct hdac_driver {scalar_t__ type; int (* match ) (struct hdac_device*,struct hdac_driver*) ;} ;
struct hdac_device {scalar_t__ type; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hdac_device* dev_to_hdac_dev (struct device*) ; 
 struct hdac_driver* drv_to_hdac_driver (struct device_driver*) ; 
 int hdac_codec_match (struct hdac_device*,struct hdac_driver*) ; 
 int stub1 (struct hdac_device*,struct hdac_driver*) ; 

__attribute__((used)) static int hda_bus_match(struct device *dev, struct device_driver *drv)
{
	struct hdac_device *hdev = dev_to_hdac_dev(dev);
	struct hdac_driver *hdrv = drv_to_hdac_driver(drv);

	if (hdev->type != hdrv->type)
		return 0;

	/*
	 * if driver provided a match function use that otherwise we will
	 * use hdac_codec_match function
	 */
	if (hdrv->match)
		return hdrv->match(hdev, hdrv);
	else
		return hdac_codec_match(hdev, hdrv);
	return 1;
}