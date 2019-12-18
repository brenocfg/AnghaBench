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
struct hdac_driver {int dummy; } ;
struct hdac_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ hdac_get_device_id (struct hdac_device*,struct hdac_driver*) ; 

__attribute__((used)) static int hdac_codec_match(struct hdac_device *dev, struct hdac_driver *drv)
{
	if (hdac_get_device_id(dev, drv))
		return 1;
	else
		return 0;
}