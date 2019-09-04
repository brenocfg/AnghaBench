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
typedef  int /*<<< orphan*/  u8 ;
struct phy_dm_struct {int* one_path_cca; int /*<<< orphan*/  rf_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGI ; 
 int /*<<< orphan*/  IGI_A ; 
 int /*<<< orphan*/  IGI_B ; 
 int /*<<< orphan*/  ODM_1T1R ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
#define  ODM_CCA_1R_A 130 
#define  ODM_CCA_1R_B 129 
#define  ODM_CCA_2R 128 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  get_igi_for_diff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void phydm_check_ap_write_dig(struct phy_dm_struct *dm,
					    u8 current_igi)
{
	switch (*dm->one_path_cca) {
	case ODM_CCA_2R:
		odm_set_bb_reg(dm, ODM_REG(IGI_A, dm), ODM_BIT(IGI, dm),
			       current_igi);

		if (dm->rf_type > ODM_1T1R)
			odm_set_bb_reg(dm, ODM_REG(IGI_B, dm), ODM_BIT(IGI, dm),
				       current_igi);
		break;
	case ODM_CCA_1R_A:
		odm_set_bb_reg(dm, ODM_REG(IGI_A, dm), ODM_BIT(IGI, dm),
			       current_igi);
		if (dm->rf_type != ODM_1T1R)
			odm_set_bb_reg(dm, ODM_REG(IGI_B, dm), ODM_BIT(IGI, dm),
				       get_igi_for_diff(current_igi));
		break;
	case ODM_CCA_1R_B:
		odm_set_bb_reg(dm, ODM_REG(IGI_B, dm), ODM_BIT(IGI, dm),
			       get_igi_for_diff(current_igi));
		if (dm->rf_type != ODM_1T1R)
			odm_set_bb_reg(dm, ODM_REG(IGI_A, dm), ODM_BIT(IGI, dm),
				       current_igi);
		break;
	}
}