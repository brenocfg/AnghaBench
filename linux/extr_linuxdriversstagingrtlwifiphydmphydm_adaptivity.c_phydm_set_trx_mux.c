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
struct phy_dm_struct {int support_ic_type; scalar_t__ rf_type; } ;
typedef  enum phydm_trx_mux_type { ____Placeholder_phydm_trx_mux_type } phydm_trx_mux_type ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ ODM_1T1R ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_CCK_RPT_FORMAT_11N ; 
 int /*<<< orphan*/  ODM_REG_CCK_RPT_FORMAT_11N_B ; 
 int /*<<< orphan*/  ODM_REG_TRMUX_11AC ; 
 int /*<<< orphan*/  ODM_REG_TRMUX_11AC_B ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 

void phydm_set_trx_mux(void *dm_void, enum phydm_trx_mux_type tx_mode,
		       enum phydm_trx_mux_type rx_mode)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		/*set TXmod to standby mode to remove outside noise affect*/
		odm_set_bb_reg(dm, ODM_REG_CCK_RPT_FORMAT_11N,
			       BIT(3) | BIT(2) | BIT(1), tx_mode);
		/*set RXmod to standby mode to remove outside noise affect*/
		odm_set_bb_reg(dm, ODM_REG_CCK_RPT_FORMAT_11N,
			       BIT(22) | BIT(21) | BIT(20), rx_mode);
		if (dm->rf_type > ODM_1T1R) {
			/*set TXmod to standby mode to rm outside noise affect*/
			odm_set_bb_reg(dm, ODM_REG_CCK_RPT_FORMAT_11N_B,
				       BIT(3) | BIT(2) | BIT(1), tx_mode);
			/*set RXmod to standby mode to rm outside noise affect*/
			odm_set_bb_reg(dm, ODM_REG_CCK_RPT_FORMAT_11N_B,
				       BIT(22) | BIT(21) | BIT(20), rx_mode);
		}
	} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		/*set TXmod to standby mode to remove outside noise affect*/
		odm_set_bb_reg(dm, ODM_REG_TRMUX_11AC,
			       BIT(11) | BIT(10) | BIT(9) | BIT(8), tx_mode);
		/*set RXmod to standby mode to remove outside noise affect*/
		odm_set_bb_reg(dm, ODM_REG_TRMUX_11AC,
			       BIT(7) | BIT(6) | BIT(5) | BIT(4), rx_mode);
		if (dm->rf_type > ODM_1T1R) {
			/*set TXmod to standby mode to rm outside noise affect*/
			odm_set_bb_reg(dm, ODM_REG_TRMUX_11AC_B,
				       BIT(11) | BIT(10) | BIT(9) | BIT(8),
				       tx_mode);
			/*set RXmod to standby mode to rm outside noise affect*/
			odm_set_bb_reg(dm, ODM_REG_TRMUX_11AC_B,
				       BIT(7) | BIT(6) | BIT(5) | BIT(4),
				       rx_mode);
		}
	}
}