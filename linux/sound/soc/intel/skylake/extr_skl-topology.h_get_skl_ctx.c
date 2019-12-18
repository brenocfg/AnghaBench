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
struct skl_dev {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static inline struct skl_dev *get_skl_ctx(struct device *dev)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);

	return bus_to_skl(bus);
}