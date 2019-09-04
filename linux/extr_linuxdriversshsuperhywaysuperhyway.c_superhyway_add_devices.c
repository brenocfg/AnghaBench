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
struct superhyway_device {TYPE_1__* resource; } ;
struct superhyway_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int superhyway_add_device (int /*<<< orphan*/ ,struct superhyway_device*,struct superhyway_bus*) ; 

int superhyway_add_devices(struct superhyway_bus *bus,
			   struct superhyway_device **devices,
			   int nr_devices)
{
	int i, ret = 0;

	for (i = 0; i < nr_devices; i++) {
		struct superhyway_device *dev = devices[i];
		ret |= superhyway_add_device(dev->resource[0].start, dev, bus);
	}

	return ret;
}