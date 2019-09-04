#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct tsensor_shared_calib {int base_cp; int base_ft; long long actual_temp_ft; long long actual_temp_cp; } ;
struct tegra_tsensor_group {long long pdiv; long long pdiv_ate; } ;
struct tegra_tsensor {long long fuse_corr_alpha; long long fuse_corr_beta; TYPE_1__* config; int /*<<< orphan*/  calib_fuse_offset; struct tegra_tsensor_group* group; } ;
typedef  long long s64 ;
typedef  long long s32 ;
typedef  scalar_t__ s16 ;
struct TYPE_2__ {long long tsample_ate; long long tsample; } ;

/* Variables and functions */
 long long CALIB_COEFFICIENT ; 
 int FUSE_TSENSOR_CALIB_FT_TS_BASE_MASK ; 
 int FUSE_TSENSOR_CALIB_FT_TS_BASE_SHIFT ; 
 int SENSOR_CONFIG2_THERMA_SHIFT ; 
 int SENSOR_CONFIG2_THERMB_SHIFT ; 
 scalar_t__ div64_s64_precise (long long,long long) ; 
 long long sign_extend32 (int,int) ; 
 int tegra_fuse_readl (int /*<<< orphan*/ ,int*) ; 

int tegra_calc_tsensor_calib(const struct tegra_tsensor *sensor,
			     const struct tsensor_shared_calib *shared,
			     u32 *calibration)
{
	const struct tegra_tsensor_group *sensor_group;
	u32 val, calib;
	s32 actual_tsensor_ft, actual_tsensor_cp;
	s32 delta_sens, delta_temp;
	s32 mult, div;
	s16 therma, thermb;
	s64 temp;
	int err;

	sensor_group = sensor->group;

	err = tegra_fuse_readl(sensor->calib_fuse_offset, &val);
	if (err)
		return err;

	actual_tsensor_cp = (shared->base_cp * 64) + sign_extend32(val, 12);
	val = (val & FUSE_TSENSOR_CALIB_FT_TS_BASE_MASK) >>
	      FUSE_TSENSOR_CALIB_FT_TS_BASE_SHIFT;
	actual_tsensor_ft = (shared->base_ft * 32) + sign_extend32(val, 12);

	delta_sens = actual_tsensor_ft - actual_tsensor_cp;
	delta_temp = shared->actual_temp_ft - shared->actual_temp_cp;

	mult = sensor_group->pdiv * sensor->config->tsample_ate;
	div = sensor->config->tsample * sensor_group->pdiv_ate;

	temp = (s64)delta_temp * (1LL << 13) * mult;
	therma = div64_s64_precise(temp, (s64)delta_sens * div);

	temp = ((s64)actual_tsensor_ft * shared->actual_temp_cp) -
		((s64)actual_tsensor_cp * shared->actual_temp_ft);
	thermb = div64_s64_precise(temp, delta_sens);

	temp = (s64)therma * sensor->fuse_corr_alpha;
	therma = div64_s64_precise(temp, CALIB_COEFFICIENT);

	temp = (s64)thermb * sensor->fuse_corr_alpha + sensor->fuse_corr_beta;
	thermb = div64_s64_precise(temp, CALIB_COEFFICIENT);

	calib = ((u16)therma << SENSOR_CONFIG2_THERMA_SHIFT) |
		((u16)thermb << SENSOR_CONFIG2_THERMB_SHIFT);

	*calibration = calib;

	return 0;
}