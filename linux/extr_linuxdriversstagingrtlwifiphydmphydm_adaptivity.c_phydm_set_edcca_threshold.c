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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_dm_struct {int support_ic_type; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE2 ; 
 int MASKLWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  REG_FPGA0_XB_LSSI_READ_BACK ; 
 int /*<<< orphan*/  REG_OFDM_0_ECCA_THRESHOLD ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void phydm_set_edcca_threshold(void *dm_void, s8 H2L, s8 L2H)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11N_SERIES)
		odm_set_bb_reg(dm, REG_OFDM_0_ECCA_THRESHOLD,
			       MASKBYTE2 | MASKBYTE0,
			       (u32)((u8)L2H | (u8)H2L << 16));
	else if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		odm_set_bb_reg(dm, REG_FPGA0_XB_LSSI_READ_BACK, MASKLWORD,
			       (u16)((u8)L2H | (u8)H2L << 8));
}