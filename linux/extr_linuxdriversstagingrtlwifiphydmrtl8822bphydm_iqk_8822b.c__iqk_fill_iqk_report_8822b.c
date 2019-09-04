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
typedef  size_t u8 ;
typedef  int u32 ;
struct dm_iqk_info {int*** iqk_fail_report; int** rxiqk_fail_code; int** rxiqk_agc; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;

/* Variables and functions */
 size_t RX_IQK ; 
 size_t SS_8822B ; 
 size_t TX_IQK ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_fill_iqk_report_8822b(void *dm_void, u8 channel)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u32 tmp1 = 0x0, tmp2 = 0x0, tmp3 = 0x0;
	u8 i;

	for (i = 0; i < SS_8822B; i++) {
		tmp1 = tmp1 +
		       ((iqk_info->iqk_fail_report[channel][i][TX_IQK] & 0x1)
			<< i);
		tmp2 = tmp2 +
		       ((iqk_info->iqk_fail_report[channel][i][RX_IQK] & 0x1)
			<< (i + 4));
		tmp3 = tmp3 + ((iqk_info->rxiqk_fail_code[channel][i] & 0x3)
			       << (i * 2 + 8));
	}
	odm_write_4byte(dm, 0x1b00, 0xf8000008);
	odm_set_bb_reg(dm, 0x1bf0, 0x0000ffff, tmp1 | tmp2 | tmp3);

	for (i = 0; i < 2; i++)
		odm_write_4byte(
			dm, 0x1be8 + (i * 4),
			(iqk_info->rxiqk_agc[channel][(i * 2) + 1] << 16) |
				iqk_info->rxiqk_agc[channel][i * 2]);
}