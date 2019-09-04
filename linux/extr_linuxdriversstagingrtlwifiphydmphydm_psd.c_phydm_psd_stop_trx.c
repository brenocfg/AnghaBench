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
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DBGPORT_PRIORITY_3 ; 
 int BIT (int) ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int STOP_TRX_FAIL ; 
 int STOP_TRX_SUCCESS ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int phydm_get_bb_dbg_port_value (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_release_bb_dbg_port (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_set_bb_dbg_port (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 phydm_psd_stop_trx(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 i;
	u8 trx_idle_success = false;
	u32 dbg_port_value = 0;

	/*[Stop TRX]----------------------------------------------------------*/
	if (!phydm_set_bb_dbg_port(dm, BB_DBGPORT_PRIORITY_3,
				   0x0)) /*set debug port to 0x0*/
		return STOP_TRX_FAIL;

	for (i = 0; i < 10000; i++) {
		dbg_port_value = phydm_get_bb_dbg_port_value(dm);
		if ((dbg_port_value & (BIT(17) | BIT(3))) ==
		    0) /* PHYTXON && CCA_all */ {
			ODM_RT_TRACE(dm, ODM_COMP_API,
				     "PSD wait for ((%d)) times\n", i);

			trx_idle_success = true;
			break;
		}
	}

	if (trx_idle_success) {
		/*pause all TX queue*/
		odm_set_bb_reg(dm, 0x520, 0xff0000, 0xff);

		if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
			/*disable CCK block*/
			odm_set_bb_reg(dm, 0x808, BIT(28), 0);
			/*disable OFDM RX CCA*/
			odm_set_bb_reg(dm, 0x838, BIT(1), 1);
		} else {
			/*TBD*/
			/* disable whole CCK block */
			odm_set_bb_reg(dm, 0x800, BIT(24), 0);
			/*[ Set IQK Matrix = 0 ] equivalent to [ Turn off CCA]*/
			odm_set_bb_reg(dm, 0xC14, MASKDWORD, 0x0);
		}

	} else {
		return STOP_TRX_FAIL;
	}

	phydm_release_bb_dbg_port(dm);

	return STOP_TRX_SUCCESS;
}