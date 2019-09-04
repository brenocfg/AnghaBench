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
typedef  int /*<<< orphan*/  u32 ;
struct mvs_phy {int phy_status; } ;
struct mvs_info {struct mvs_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MODE6_LATECLK ; 
 int PHY_NEG_SPP_PHYS_LINK_RATE_MASK ; 
 int PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET ; 
 int SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  VSR_PHY_MODE6 ; 
 int /*<<< orphan*/  mvs_read_port_vsr_data (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_port_vsr_addr (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_write_port_vsr_data (struct mvs_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvs_64xx_phy_work_around(struct mvs_info *mvi, int i)
{
	u32 tmp;
	struct mvs_phy *phy = &mvi->phy[i];
	mvs_write_port_vsr_addr(mvi, i, VSR_PHY_MODE6);
	tmp = mvs_read_port_vsr_data(mvi, i);
	if (((phy->phy_status & PHY_NEG_SPP_PHYS_LINK_RATE_MASK) >>
	     PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET) ==
		SAS_LINK_RATE_1_5_GBPS)
		tmp &= ~PHY_MODE6_LATECLK;
	else
		tmp |= PHY_MODE6_LATECLK;
	mvs_write_port_vsr_data(mvi, i, tmp);
}