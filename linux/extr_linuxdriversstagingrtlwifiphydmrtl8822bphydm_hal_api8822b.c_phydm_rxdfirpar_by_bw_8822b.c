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
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_bw { ____Placeholder_odm_bw } odm_bw ;

/* Variables and functions */
 int BIT (int) ; 
 int ODM_BW40M ; 
 int ODM_BW80M ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

__attribute__((used)) static void phydm_rxdfirpar_by_bw_8822b(struct phy_dm_struct *dm,
					enum odm_bw bandwidth)
{
	if (bandwidth == ODM_BW40M) {
		/* RX DFIR for BW40 */
		odm_set_bb_reg(dm, 0x948, BIT(29) | BIT(28), 0x1);
		odm_set_bb_reg(dm, 0x94c, BIT(29) | BIT(28), 0x0);
		odm_set_bb_reg(dm, 0xc20, BIT(31), 0x0);
		odm_set_bb_reg(dm, 0xe20, BIT(31), 0x0);
	} else if (bandwidth == ODM_BW80M) {
		/* RX DFIR for BW80 */
		odm_set_bb_reg(dm, 0x948, BIT(29) | BIT(28), 0x2);
		odm_set_bb_reg(dm, 0x94c, BIT(29) | BIT(28), 0x1);
		odm_set_bb_reg(dm, 0xc20, BIT(31), 0x0);
		odm_set_bb_reg(dm, 0xe20, BIT(31), 0x0);
	} else {
		/* RX DFIR for BW20, BW10 and BW5*/
		odm_set_bb_reg(dm, 0x948, BIT(29) | BIT(28), 0x2);
		odm_set_bb_reg(dm, 0x94c, BIT(29) | BIT(28), 0x2);
		odm_set_bb_reg(dm, 0xc20, BIT(31), 0x1);
		odm_set_bb_reg(dm, 0xe20, BIT(31), 0x1);
	}
}