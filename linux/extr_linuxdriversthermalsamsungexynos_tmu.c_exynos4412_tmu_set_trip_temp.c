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
typedef  int u32 ;
struct exynos_tmu_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EXYNOS_THD_TEMP_RISE ; 
 scalar_t__ EXYNOS_TMU_REG_CONTROL ; 
 int EXYNOS_TMU_THERM_TRIP_EN_SHIFT ; 
 int readl (scalar_t__) ; 
 int temp_to_code (struct exynos_tmu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos4412_tmu_set_trip_temp(struct exynos_tmu_data *data,
					 int trip, u8 temp)
{
	u32 th, con;

	th = readl(data->base + EXYNOS_THD_TEMP_RISE);
	th &= ~(0xff << 8 * trip);
	th |= temp_to_code(data, temp) << 8 * trip;
	writel(th, data->base + EXYNOS_THD_TEMP_RISE);

	if (trip == 3) {
		con = readl(data->base + EXYNOS_TMU_REG_CONTROL);
		con |= (1 << EXYNOS_TMU_THERM_TRIP_EN_SHIFT);
		writel(con, data->base + EXYNOS_TMU_REG_CONTROL);
	}
}