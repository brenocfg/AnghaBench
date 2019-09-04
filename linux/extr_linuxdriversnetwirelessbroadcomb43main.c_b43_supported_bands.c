#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int type; } ;
struct b43_wldev {TYPE_1__ phy; TYPE_2__* dev; } ;
struct TYPE_6__ {int dev_id; } ;
struct TYPE_5__ {TYPE_3__* bus_sprom; } ;

/* Variables and functions */
#define  B43_PHYTYPE_G 132 
#define  B43_PHYTYPE_HT 131 
#define  B43_PHYTYPE_LCN 130 
#define  B43_PHYTYPE_LP 129 
#define  B43_PHYTYPE_N 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static void b43_supported_bands(struct b43_wldev *dev, bool *have_2ghz_phy,
				bool *have_5ghz_phy)
{
	u16 dev_id = 0;

#ifdef CONFIG_B43_BCMA
	if (dev->dev->bus_type == B43_BUS_BCMA &&
	    dev->dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI)
		dev_id = dev->dev->bdev->bus->host_pci->device;
#endif
#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI)
		dev_id = dev->dev->sdev->bus->host_pci->device;
#endif
	/* Override with SPROM value if available */
	if (dev->dev->bus_sprom->dev_id)
		dev_id = dev->dev->bus_sprom->dev_id;

	/* Note: below IDs can be "virtual" (not maching e.g. real PCI ID) */
	switch (dev_id) {
	case 0x4324: /* BCM4306 */
	case 0x4312: /* BCM4311 */
	case 0x4319: /* BCM4318 */
	case 0x4328: /* BCM4321 */
	case 0x432b: /* BCM4322 */
	case 0x4350: /* BCM43222 */
	case 0x4353: /* BCM43224 */
	case 0x0576: /* BCM43224 */
	case 0x435f: /* BCM6362 */
	case 0x4331: /* BCM4331 */
	case 0x4359: /* BCM43228 */
	case 0x43a0: /* BCM4360 */
	case 0x43b1: /* BCM4352 */
		/* Dual band devices */
		*have_2ghz_phy = true;
		*have_5ghz_phy = true;
		return;
	case 0x4321: /* BCM4306 */
		/* There are 14e4:4321 PCI devs with 2.4 GHz BCM4321 (N-PHY) */
		if (dev->phy.type != B43_PHYTYPE_G)
			break;
		/* fall through */
	case 0x4313: /* BCM4311 */
	case 0x431a: /* BCM4318 */
	case 0x432a: /* BCM4321 */
	case 0x432d: /* BCM4322 */
	case 0x4352: /* BCM43222 */
	case 0x435a: /* BCM43228 */
	case 0x4333: /* BCM4331 */
	case 0x43a2: /* BCM4360 */
	case 0x43b3: /* BCM4352 */
		/* 5 GHz only devices */
		*have_2ghz_phy = false;
		*have_5ghz_phy = true;
		return;
	}

	/* As a fallback, try to guess using PHY type */
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_LP:
	case B43_PHYTYPE_HT:
	case B43_PHYTYPE_LCN:
		*have_2ghz_phy = true;
		*have_5ghz_phy = false;
		return;
	}

	B43_WARN_ON(1);
}