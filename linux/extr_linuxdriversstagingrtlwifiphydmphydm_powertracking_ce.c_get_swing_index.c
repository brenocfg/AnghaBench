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
typedef  size_t u32 ;
struct phy_dm_struct {scalar_t__ support_ic_type; } ;

/* Variables and functions */
 scalar_t__ ODM_RTL8188E ; 
 scalar_t__ ODM_RTL8188F ; 
 scalar_t__ ODM_RTL8192E ; 
 scalar_t__ ODM_RTL8703B ; 
 scalar_t__ ODM_RTL8723B ; 
 size_t OFDM_TABLE_SIZE ; 
 int /*<<< orphan*/  REG_OFDM_0_XA_TX_IQ_IMBALANCE ; 
 size_t odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 size_t* ofdm_swing_table ; 
 size_t* ofdm_swing_table_new ; 

__attribute__((used)) static u8 get_swing_index(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 i = 0;
	u32 bb_swing;
	u32 swing_table_size;
	u32 *swing_table;

	if (dm->support_ic_type == ODM_RTL8188E ||
	    dm->support_ic_type == ODM_RTL8723B ||
	    dm->support_ic_type == ODM_RTL8192E ||
	    dm->support_ic_type == ODM_RTL8188F ||
	    dm->support_ic_type == ODM_RTL8703B) {
		bb_swing = odm_get_bb_reg(dm, REG_OFDM_0_XA_TX_IQ_IMBALANCE,
					  0xFFC00000);

		swing_table = ofdm_swing_table_new;
		swing_table_size = OFDM_TABLE_SIZE;
	} else {
		{
			bb_swing = 0;
			swing_table = ofdm_swing_table;
			swing_table_size = OFDM_TABLE_SIZE;
		}
	}

	for (i = 0; i < swing_table_size; ++i) {
		u32 table_value = swing_table[i];

		if (table_value >= 0x100000)
			table_value >>= 22;
		if (bb_swing == table_value)
			break;
	}
	return i;
}