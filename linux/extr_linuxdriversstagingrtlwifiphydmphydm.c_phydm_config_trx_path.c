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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCA_PATHDIV_DISABLE ; 
 int /*<<< orphan*/  CCA_PATHDIV_ENABLE ; 
 int /*<<< orphan*/  PHYDM_A ; 
 int /*<<< orphan*/  PHYDM_AB ; 
 int /*<<< orphan*/  PHYDM_B ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  phydm_config_cck_rx_antenna_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_config_cck_rx_path (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_config_ofdm_rx_path (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  phydm_config_ofdm_tx_path (struct phy_dm_struct*,int) ; 

void phydm_config_trx_path(void *dm_void, u32 *const dm_value, u32 *_used,
			   char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;

	/* CCK */
	if (dm_value[0] == 0) {
		if (dm_value[1] == 1) { /*TX*/
			if (dm_value[2] == 1)
				odm_set_bb_reg(dm, 0xa04, 0xf0000000, 0x8);
			else if (dm_value[2] == 2)
				odm_set_bb_reg(dm, 0xa04, 0xf0000000, 0x4);
			else if (dm_value[2] == 3)
				odm_set_bb_reg(dm, 0xa04, 0xf0000000, 0xc);
		} else if (dm_value[1] == 2) { /*RX*/

			phydm_config_cck_rx_antenna_init(dm);

			if (dm_value[2] == 1)
				phydm_config_cck_rx_path(dm, PHYDM_A,
							 CCA_PATHDIV_DISABLE);
			else if (dm_value[2] == 2)
				phydm_config_cck_rx_path(dm, PHYDM_B,
							 CCA_PATHDIV_DISABLE);
			else if (dm_value[2] == 3 &&
				 dm_value[3] == 1) /*enable path diversity*/
				phydm_config_cck_rx_path(dm, PHYDM_AB,
							 CCA_PATHDIV_ENABLE);
			else if (dm_value[2] == 3 && dm_value[3] != 1)
				phydm_config_cck_rx_path(dm, PHYDM_B,
							 CCA_PATHDIV_DISABLE);
		}
	}
	/* OFDM */
	else if (dm_value[0] == 1) {
		if (dm_value[1] == 1) { /*TX*/
			phydm_config_ofdm_tx_path(dm, dm_value[2]);
			/**/
		} else if (dm_value[1] == 2) { /*RX*/
			phydm_config_ofdm_rx_path(dm, dm_value[2]);
			/**/
		}
	}

	PHYDM_SNPRINTF(
		output + used, out_len - used,
		"PHYDM Set path [%s] [%s] = [%s%s%s%s]\n",
		(dm_value[0] == 1) ? "OFDM" : "CCK",
		(dm_value[1] == 1) ? "TX" : "RX",
		(dm_value[2] & 0x1) ? "A" : "", (dm_value[2] & 0x2) ? "B" : "",
		(dm_value[2] & 0x4) ? "C" : "", (dm_value[2] & 0x8) ? "D" : "");
}