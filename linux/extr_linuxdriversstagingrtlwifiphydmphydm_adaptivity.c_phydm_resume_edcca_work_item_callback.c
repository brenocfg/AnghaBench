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
struct adaptivity_statistics {scalar_t__ backup_h2l; scalar_t__ backup_l2h; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE2 ; 
 int MASKLWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int /*<<< orphan*/  REG_FPGA0_XB_LSSI_READ_BACK ; 
 int /*<<< orphan*/  REG_OFDM_0_ECCA_THRESHOLD ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void phydm_resume_edcca_work_item_callback(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);

	if (dm->support_ic_type & ODM_IC_11N_SERIES)
		odm_set_bb_reg(dm, REG_OFDM_0_ECCA_THRESHOLD,
			       MASKBYTE2 | MASKBYTE0,
			       (u32)((u8)adaptivity->backup_l2h |
				     (u8)adaptivity->backup_h2l << 16));
	else if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		odm_set_bb_reg(dm, REG_FPGA0_XB_LSSI_READ_BACK, MASKLWORD,
			       (u16)((u8)adaptivity->backup_l2h |
				     (u8)adaptivity->backup_h2l << 8));
}