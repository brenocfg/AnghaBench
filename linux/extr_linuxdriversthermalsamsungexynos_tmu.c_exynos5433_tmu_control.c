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
struct thermal_zone_device {int dummy; } ;
struct platform_device {int dummy; } ;
struct exynos_tmu_data {unsigned int ntrip; scalar_t__ base; struct thermal_zone_device* tzd; } ;

/* Variables and functions */
 unsigned int EXYNOS5433_PD_DET_EN ; 
 scalar_t__ EXYNOS5433_TMU_PD_DET_EN ; 
 scalar_t__ EXYNOS5433_TMU_REG_INTEN ; 
 unsigned int EXYNOS7_TMU_INTEN_RISE0_SHIFT ; 
 int EXYNOS_TMU_CORE_EN_SHIFT ; 
 unsigned int EXYNOS_TMU_INTEN_FALL0_SHIFT ; 
 scalar_t__ EXYNOS_TMU_REG_CONTROL ; 
 unsigned int get_con_reg (struct exynos_tmu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_thermal_is_trip_valid (struct thermal_zone_device*,unsigned int) ; 
 struct exynos_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void exynos5433_tmu_control(struct platform_device *pdev, bool on)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);
	struct thermal_zone_device *tz = data->tzd;
	unsigned int con, interrupt_en = 0, pd_det_en, i;

	con = get_con_reg(data, readl(data->base + EXYNOS_TMU_REG_CONTROL));

	if (on) {
		for (i = 0; i < data->ntrip; i++) {
			if (!of_thermal_is_trip_valid(tz, i))
				continue;

			interrupt_en |=
				(1 << (EXYNOS7_TMU_INTEN_RISE0_SHIFT + i));
		}

		interrupt_en |=
			interrupt_en << EXYNOS_TMU_INTEN_FALL0_SHIFT;

		con |= (1 << EXYNOS_TMU_CORE_EN_SHIFT);
	} else
		con &= ~(1 << EXYNOS_TMU_CORE_EN_SHIFT);

	pd_det_en = on ? EXYNOS5433_PD_DET_EN : 0;

	writel(pd_det_en, data->base + EXYNOS5433_TMU_PD_DET_EN);
	writel(interrupt_en, data->base + EXYNOS5433_TMU_REG_INTEN);
	writel(con, data->base + EXYNOS_TMU_REG_CONTROL);
}