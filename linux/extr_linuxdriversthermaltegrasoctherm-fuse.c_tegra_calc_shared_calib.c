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
struct tsensor_shared_calib {int base_cp; int base_ft; int actual_temp_cp; int actual_temp_ft; } ;
struct tegra_soctherm_fuse {int fuse_base_cp_mask; int fuse_base_cp_shift; int fuse_base_ft_mask; int fuse_base_ft_shift; int fuse_shift_ft_mask; int fuse_shift_ft_shift; scalar_t__ fuse_spare_realignment; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ FUSE_TSENSOR_COMMON ; 
 int NOMINAL_CALIB_CP ; 
 int NOMINAL_CALIB_FT ; 
 int sign_extend32 (int,int) ; 
 int tegra_fuse_readl (scalar_t__,int*) ; 

int tegra_calc_shared_calib(const struct tegra_soctherm_fuse *tfuse,
			    struct tsensor_shared_calib *shared)
{
	u32 val;
	s32 shifted_cp, shifted_ft;
	int err;

	err = tegra_fuse_readl(FUSE_TSENSOR_COMMON, &val);
	if (err)
		return err;

	shared->base_cp = (val & tfuse->fuse_base_cp_mask) >>
			  tfuse->fuse_base_cp_shift;
	shared->base_ft = (val & tfuse->fuse_base_ft_mask) >>
			  tfuse->fuse_base_ft_shift;

	shifted_ft = (val & tfuse->fuse_shift_ft_mask) >>
		     tfuse->fuse_shift_ft_shift;
	shifted_ft = sign_extend32(shifted_ft, 4);

	if (tfuse->fuse_spare_realignment) {
		err = tegra_fuse_readl(tfuse->fuse_spare_realignment, &val);
		if (err)
			return err;
	}

	shifted_cp = sign_extend32(val, 5);

	shared->actual_temp_cp = 2 * NOMINAL_CALIB_CP + shifted_cp;
	shared->actual_temp_ft = 2 * NOMINAL_CALIB_FT + shifted_ft;

	return 0;
}