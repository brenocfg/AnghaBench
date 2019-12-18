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
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct hdac_driver* drv_to_hdac_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hdac_driver *get_hdrv(struct device *dev)
{
	struct hdac_driver *hdrv = drv_to_hdac_driver(dev->driver);
	return hdrv;
}