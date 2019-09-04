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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 scalar_t__ FREQ_POSITIVE ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,scalar_t__) ; 
 scalar_t__ odm_read_1byte (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,scalar_t__) ; 

__attribute__((used)) static void phydm_set_csi_mask_reg(void *dm_void, u32 tone_idx_tmp,
				   u8 tone_direction)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 byte_offset, bit_offset;
	u32 target_reg;
	u8 reg_tmp_value;
	u32 tone_num = 64;
	u32 tone_num_shift = 0;
	u32 csi_mask_reg_p = 0, csi_mask_reg_n = 0;

	/* calculate real tone idx*/
	if ((tone_idx_tmp % 10) >= 5)
		tone_idx_tmp += 10;

	tone_idx_tmp = (tone_idx_tmp / 10);

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		tone_num = 64;
		csi_mask_reg_p = 0xD40;
		csi_mask_reg_n = 0xD48;

	} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		tone_num = 128;
		csi_mask_reg_p = 0x880;
		csi_mask_reg_n = 0x890;
	}

	if (tone_direction == FREQ_POSITIVE) {
		if (tone_idx_tmp >= (tone_num - 1))
			tone_idx_tmp = (tone_num - 1);

		byte_offset = (u8)(tone_idx_tmp >> 3);
		bit_offset = (u8)(tone_idx_tmp & 0x7);
		target_reg = csi_mask_reg_p + byte_offset;

	} else {
		tone_num_shift = tone_num;

		if (tone_idx_tmp >= tone_num)
			tone_idx_tmp = tone_num;

		tone_idx_tmp = tone_num - tone_idx_tmp;

		byte_offset = (u8)(tone_idx_tmp >> 3);
		bit_offset = (u8)(tone_idx_tmp & 0x7);
		target_reg = csi_mask_reg_n + byte_offset;
	}

	reg_tmp_value = odm_read_1byte(dm, target_reg);
	ODM_RT_TRACE(dm, ODM_COMP_API,
		     "Pre Mask tone idx[%d]:  Reg0x%x = ((0x%x))\n",
		     (tone_idx_tmp + tone_num_shift), target_reg,
		     reg_tmp_value);
	reg_tmp_value |= BIT(bit_offset);
	odm_write_1byte(dm, target_reg, reg_tmp_value);
	ODM_RT_TRACE(dm, ODM_COMP_API,
		     "New Mask tone idx[%d]:  Reg0x%x = ((0x%x))\n",
		     (tone_idx_tmp + tone_num_shift), target_reg,
		     reg_tmp_value);
}