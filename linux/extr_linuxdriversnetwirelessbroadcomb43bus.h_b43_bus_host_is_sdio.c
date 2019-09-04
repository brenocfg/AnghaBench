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
struct b43_bus_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool b43_bus_host_is_sdio(struct b43_bus_dev *dev)
{
#ifdef CONFIG_B43_SSB
	return (dev->bus_type == B43_BUS_SSB &&
		dev->sdev->bus->bustype == SSB_BUSTYPE_SDIO);
#else
	return false;
#endif
}