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
struct platform_device {int dummy; } ;
struct exynos_tmu_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EXYNOS_TMU_REG_TRIMINFO ; 
 struct exynos_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sanitize_temp_error (struct exynos_tmu_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos4210_tmu_initialize(struct platform_device *pdev)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);

	sanitize_temp_error(data, readl(data->base + EXYNOS_TMU_REG_TRIMINFO));
}