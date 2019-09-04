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
struct phy_dm_struct {int dummy; } ;
struct dm_iqk_info {int**** iqk_cfir_real; int**** iqk_cfir_imag; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

__attribute__((used)) static inline void phydm_set_iqk_cfir(struct phy_dm_struct *dm,
				      struct dm_iqk_info *iqk_info, u8 path)
{
	u8 idx, i;
	u32 tmp;

	for (idx = 0; idx < 2; idx++) {
		odm_set_bb_reg(dm, 0x1b00, MASKDWORD, 0xf8000008 | path << 1);

		if (idx == 0)
			odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12), 0x3);
		else
			odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12), 0x1);

		odm_set_bb_reg(dm, 0x1bd4,
			       BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16),
			       0x10);

		for (i = 0; i < 8; i++) {
			odm_set_bb_reg(dm, 0x1bd8, MASKDWORD,
				       0xe0000001 + (i * 4));
			tmp = odm_get_bb_reg(dm, 0x1bfc, MASKDWORD);
			iqk_info->iqk_cfir_real[0][path][idx][i] =
				(tmp & 0x0fff0000) >> 16;
			iqk_info->iqk_cfir_imag[0][path][idx][i] = tmp & 0xfff;
		}
	}
}