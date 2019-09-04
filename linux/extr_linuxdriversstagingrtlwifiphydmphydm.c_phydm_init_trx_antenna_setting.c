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
typedef  int u8 ;
struct phy_dm_struct {int support_ic_type; int tx_ant_status; int rx_ant_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_RX_PATH ; 
 int /*<<< orphan*/  BB_TX_PATH ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int ODM_RTL8710B ; 
 int ODM_RTL8723D ; 
 int ODM_RTL8814A ; 
 int ODM_RTL8821C ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_init_trx_antenna_setting(struct phy_dm_struct *dm)
{
	/*#if (RTL8814A_SUPPORT == 1)*/

	if (dm->support_ic_type & (ODM_RTL8814A)) {
		u8 rx_ant = 0, tx_ant = 0;

		rx_ant = (u8)odm_get_bb_reg(dm, ODM_REG(BB_RX_PATH, dm),
					    ODM_BIT(BB_RX_PATH, dm));
		tx_ant = (u8)odm_get_bb_reg(dm, ODM_REG(BB_TX_PATH, dm),
					    ODM_BIT(BB_TX_PATH, dm));
		dm->tx_ant_status = (tx_ant & 0xf);
		dm->rx_ant_status = (rx_ant & 0xf);
	} else if (dm->support_ic_type & (ODM_RTL8723D | ODM_RTL8821C |
					  ODM_RTL8710B)) { /* JJ ADD 20161014 */
		dm->tx_ant_status = 0x1;
		dm->rx_ant_status = 0x1;
	}
	/*#endif*/
}