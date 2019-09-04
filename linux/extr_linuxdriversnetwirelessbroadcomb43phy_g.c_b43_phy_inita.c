#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct b43_phy {int rev; } ;
struct b43_wldev {TYPE_2__* dev; struct b43_phy phy; } ;
struct TYPE_4__ {TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_PACTRL ; 
 int /*<<< orphan*/  B43_PHY_ENCORE ; 
 int B43_PHY_ENCORE_EN ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_wa_all (struct b43_wldev*) ; 
 int /*<<< orphan*/  might_sleep () ; 

__attribute__((used)) static void b43_phy_inita(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	might_sleep();

	if (phy->rev >= 6) {
		if (b43_phy_read(dev, B43_PHY_ENCORE) & B43_PHY_ENCORE_EN)
			b43_phy_set(dev, B43_PHY_ENCORE, 0x0010);
		else
			b43_phy_mask(dev, B43_PHY_ENCORE, ~0x1010);
	}

	b43_wa_all(dev);

	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		b43_phy_maskset(dev, B43_PHY_OFDM(0x6E), 0xE000, 0x3CF);
}