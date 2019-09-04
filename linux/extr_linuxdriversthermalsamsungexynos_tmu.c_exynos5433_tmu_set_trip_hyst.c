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
struct exynos_tmu_data {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int EXYNOS5433_THD_TEMP_FALL3_0 ; 
 unsigned int EXYNOS5433_THD_TEMP_FALL7_4 ; 
 int readl (scalar_t__) ; 
 unsigned int temp_to_code (struct exynos_tmu_data*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos5433_tmu_set_trip_hyst(struct exynos_tmu_data *data,
					 int trip, u8 temp, u8 hyst)
{
	unsigned int reg_off, j;
	u32 th;

	if (trip > 3) {
		reg_off = EXYNOS5433_THD_TEMP_FALL7_4;
		j = trip - 4;
	} else {
		reg_off = EXYNOS5433_THD_TEMP_FALL3_0;
		j = trip;
	}

	th = readl(data->base + reg_off);
	th &= ~(0xff << j * 8);
	th |= (temp_to_code(data, temp - hyst) << j * 8);
	writel(th, data->base + reg_off);
}