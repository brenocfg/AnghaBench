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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct exynos_tmu_data {int /*<<< orphan*/  cal_type; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int EXYNOS5433_TRIMINFO_CALIB_SEL_MASK ; 
 unsigned int EXYNOS5433_TRIMINFO_CALIB_SEL_SHIFT ; 
#define  EXYNOS5433_TRIMINFO_ONE_POINT_TRIMMING 129 
 unsigned int EXYNOS5433_TRIMINFO_SENSOR_ID_MASK ; 
 unsigned int EXYNOS5433_TRIMINFO_SENSOR_ID_SHIFT ; 
#define  EXYNOS5433_TRIMINFO_TWO_POINT_TRIMMING 128 
 scalar_t__ EXYNOS_TMU_REG_TRIMINFO ; 
 int /*<<< orphan*/  TYPE_ONE_POINT_TRIMMING ; 
 int /*<<< orphan*/  TYPE_TWO_POINT_TRIMMING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct exynos_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  sanitize_temp_error (struct exynos_tmu_data*,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void exynos5433_tmu_initialize(struct platform_device *pdev)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);
	unsigned int trim_info;
	int sensor_id, cal_type;

	trim_info = readl(data->base + EXYNOS_TMU_REG_TRIMINFO);
	sanitize_temp_error(data, trim_info);

	/* Read the temperature sensor id */
	sensor_id = (trim_info & EXYNOS5433_TRIMINFO_SENSOR_ID_MASK)
				>> EXYNOS5433_TRIMINFO_SENSOR_ID_SHIFT;
	dev_info(&pdev->dev, "Temperature sensor ID: 0x%x\n", sensor_id);

	/* Read the calibration mode */
	writel(trim_info, data->base + EXYNOS_TMU_REG_TRIMINFO);
	cal_type = (trim_info & EXYNOS5433_TRIMINFO_CALIB_SEL_MASK)
				>> EXYNOS5433_TRIMINFO_CALIB_SEL_SHIFT;

	switch (cal_type) {
	case EXYNOS5433_TRIMINFO_TWO_POINT_TRIMMING:
		data->cal_type = TYPE_TWO_POINT_TRIMMING;
		break;
	case EXYNOS5433_TRIMINFO_ONE_POINT_TRIMMING:
	default:
		data->cal_type = TYPE_ONE_POINT_TRIMMING;
		break;
	}

	dev_info(&pdev->dev, "Calibration type is %d-point calibration\n",
			cal_type ?  2 : 1);
}