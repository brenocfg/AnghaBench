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
typedef  int u32 ;
struct mvs_phy {int phy_type; } ;
struct mvs_info {struct mvs_phy* phy; } ;

/* Variables and functions */
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 int /*<<< orphan*/  VSR_PHY_MODE3 ; 
 int mvs_read_port_vsr_data (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_port_vsr_addr (struct mvs_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvs_94xx_detect_porttype(struct mvs_info *mvi, int i)
{
	u32 reg;
	struct mvs_phy *phy = &mvi->phy[i];
	u32 phy_status;

	mvs_write_port_vsr_addr(mvi, i, VSR_PHY_MODE3);
	reg = mvs_read_port_vsr_data(mvi, i);
	phy_status = ((reg & 0x3f0000) >> 16) & 0xff;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	switch (phy_status) {
	case 0x10:
		phy->phy_type |= PORT_TYPE_SAS;
		break;
	case 0x1d:
	default:
		phy->phy_type |= PORT_TYPE_SATA;
		break;
	}
}