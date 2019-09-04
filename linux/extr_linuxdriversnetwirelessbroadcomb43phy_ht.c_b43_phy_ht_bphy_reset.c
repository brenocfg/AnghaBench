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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_PSM_PHY_HDR ; 
 int /*<<< orphan*/  B43_PHY_B_BBCFG ; 
 int B43_PHY_B_BBCFG_RSTCCA ; 
 int B43_PHY_B_BBCFG_RSTRX ; 
 int B43_PSM_HDR_MAC_PHY_FORCE_CLK ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_phy_ht_bphy_reset(struct b43_wldev *dev, bool reset)
{
	u16 tmp;

	tmp = b43_read16(dev, B43_MMIO_PSM_PHY_HDR);
	b43_write16(dev, B43_MMIO_PSM_PHY_HDR,
		    tmp | B43_PSM_HDR_MAC_PHY_FORCE_CLK);

	/* Put BPHY in or take it out of the reset */
	if (reset)
		b43_phy_set(dev, B43_PHY_B_BBCFG,
			    B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX);
	else
		b43_phy_mask(dev, B43_PHY_B_BBCFG,
			     (u16)~(B43_PHY_B_BBCFG_RSTCCA |
				    B43_PHY_B_BBCFG_RSTRX));

	b43_write16(dev, B43_MMIO_PSM_PHY_HDR, tmp);
}