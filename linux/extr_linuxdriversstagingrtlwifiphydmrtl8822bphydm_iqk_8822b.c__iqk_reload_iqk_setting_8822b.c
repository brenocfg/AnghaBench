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
typedef  int u16 ;
struct dm_iqk_info {int** lok_idac; int**** iqk_cfir_real; int**** iqk_cfir_imag; int** bypass_iqk; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int,int,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_reload_iqk_setting_8822b(
	struct phy_dm_struct *dm, u8 channel,
	u8 reload_idx /*1: reload TX, 2: reload LO, TX, RX*/
	)
{
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u8 i, path, idx;
	u16 iqk_apply[2] = {0xc94, 0xe94};

	for (path = 0; path < 2; path++) {
		if (reload_idx == 2) {
			odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0xdf,
				       BIT(4), 0x1);
			odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x58,
				       RFREGOFFSETMASK,
				       iqk_info->lok_idac[channel][path]);
		}

		for (idx = 0; idx < reload_idx; idx++) {
			odm_set_bb_reg(dm, 0x1b00, MASKDWORD,
				       0xf8000008 | path << 1);
			odm_set_bb_reg(dm, 0x1b2c, MASKDWORD, 0x7);
			odm_set_bb_reg(dm, 0x1b38, MASKDWORD, 0x20000000);
			odm_set_bb_reg(dm, 0x1b3c, MASKDWORD, 0x20000000);
			odm_set_bb_reg(dm, 0x1bcc, MASKDWORD, 0x00000000);

			if (idx == 0)
				odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12),
					       0x3);
			else
				odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12),
					       0x1);

			odm_set_bb_reg(dm, 0x1bd4, BIT(20) | BIT(19) | BIT(18) |
							   BIT(17) | BIT(16),
				       0x10);

			for (i = 0; i < 8; i++) {
				odm_write_4byte(
					dm, 0x1bd8,
					((0xc0000000 >> idx) + 0x3) + (i * 4) +
						(iqk_info->iqk_cfir_real
							 [channel][path][idx][i]
						 << 9));
				odm_write_4byte(
					dm, 0x1bd8,
					((0xc0000000 >> idx) + 0x1) + (i * 4) +
						(iqk_info->iqk_cfir_imag
							 [channel][path][idx][i]
						 << 9));
			}
		}
		odm_set_bb_reg(dm, iqk_apply[path], MASKDWORD,
			       iqk_info->bypass_iqk[channel][path]);

		odm_set_bb_reg(dm, 0x1bd8, MASKDWORD, 0x0);
		odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12), 0x0);
	}
}