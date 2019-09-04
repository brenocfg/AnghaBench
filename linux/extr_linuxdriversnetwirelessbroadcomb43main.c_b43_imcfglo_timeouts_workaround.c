#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ssb_bus {int chip_id; int chip_rev; } ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_5__ {struct ssb_bus* bus; } ;
struct TYPE_4__ {TYPE_2__* sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_IMCFGLO ; 
 int SSB_IMCFGLO_REQTO ; 
 int SSB_IMCFGLO_SERTO ; 
 int /*<<< orphan*/  ssb_commit_settings (struct ssb_bus*) ; 
 int ssb_read32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_imcfglo_timeouts_workaround(struct b43_wldev *dev)
{
	struct ssb_bus *bus;
	u32 tmp;

#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type != B43_BUS_SSB)
		return;
#else
	return;
#endif

	bus = dev->dev->sdev->bus;

	if ((bus->chip_id == 0x4311 && bus->chip_rev == 2) ||
	    (bus->chip_id == 0x4312)) {
		tmp = ssb_read32(dev->dev->sdev, SSB_IMCFGLO);
		tmp &= ~SSB_IMCFGLO_REQTO;
		tmp &= ~SSB_IMCFGLO_SERTO;
		tmp |= 0x3;
		ssb_write32(dev->dev->sdev, SSB_IMCFGLO, tmp);
		ssb_commit_settings(bus);
	}
}