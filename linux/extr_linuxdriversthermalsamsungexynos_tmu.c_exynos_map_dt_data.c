#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct exynos_tmu_data {scalar_t__ id; scalar_t__ irq; int soc; int ntrip; int gain; int reference_voltage; int efuse_value; int min_efuse_value; int max_efuse_value; void* base_second; int /*<<< orphan*/  cal_type; void* tmu_clear_irqs; void* tmu_set_emulation; void* tmu_read; void* tmu_control; int /*<<< orphan*/  tmu_initialize; int /*<<< orphan*/  tmu_set_trip_hyst; int /*<<< orphan*/  tmu_set_trip_temp; void* base; } ;
typedef  enum soc_type { ____Placeholder_soc_type } soc_type ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXYNOS5433_G3D_BASE ; 
#define  SOC_ARCH_EXYNOS3250 136 
#define  SOC_ARCH_EXYNOS4210 135 
#define  SOC_ARCH_EXYNOS4412 134 
#define  SOC_ARCH_EXYNOS5250 133 
#define  SOC_ARCH_EXYNOS5260 132 
#define  SOC_ARCH_EXYNOS5420 131 
#define  SOC_ARCH_EXYNOS5420_TRIMINFO 130 
#define  SOC_ARCH_EXYNOS5433 129 
#define  SOC_ARCH_EXYNOS7 128 
 int /*<<< orphan*/  TYPE_ONE_POINT_TRIMMING ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* exynos4210_tmu_clear_irqs ; 
 void* exynos4210_tmu_control ; 
 int /*<<< orphan*/  exynos4210_tmu_initialize ; 
 void* exynos4210_tmu_read ; 
 int /*<<< orphan*/  exynos4210_tmu_set_trip_hyst ; 
 int /*<<< orphan*/  exynos4210_tmu_set_trip_temp ; 
 int /*<<< orphan*/  exynos4412_tmu_initialize ; 
 void* exynos4412_tmu_read ; 
 void* exynos4412_tmu_set_emulation ; 
 int /*<<< orphan*/  exynos4412_tmu_set_trip_hyst ; 
 int /*<<< orphan*/  exynos4412_tmu_set_trip_temp ; 
 void* exynos5433_tmu_control ; 
 int /*<<< orphan*/  exynos5433_tmu_initialize ; 
 int /*<<< orphan*/  exynos5433_tmu_set_trip_hyst ; 
 int /*<<< orphan*/  exynos5433_tmu_set_trip_temp ; 
 void* exynos7_tmu_control ; 
 int /*<<< orphan*/  exynos7_tmu_initialize ; 
 void* exynos7_tmu_read ; 
 int /*<<< orphan*/  exynos7_tmu_set_trip_hyst ; 
 int /*<<< orphan*/  exynos7_tmu_set_trip_temp ; 
 scalar_t__ irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_address_to_resource (int /*<<< orphan*/ ,int,struct resource*) ; 
 scalar_t__ of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 struct exynos_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int exynos_map_dt_data(struct platform_device *pdev)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);
	struct resource res;

	if (!data || !pdev->dev.of_node)
		return -ENODEV;

	data->id = of_alias_get_id(pdev->dev.of_node, "tmuctrl");
	if (data->id < 0)
		data->id = 0;

	data->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (data->irq <= 0) {
		dev_err(&pdev->dev, "failed to get IRQ\n");
		return -ENODEV;
	}

	if (of_address_to_resource(pdev->dev.of_node, 0, &res)) {
		dev_err(&pdev->dev, "failed to get Resource 0\n");
		return -ENODEV;
	}

	data->base = devm_ioremap(&pdev->dev, res.start, resource_size(&res));
	if (!data->base) {
		dev_err(&pdev->dev, "Failed to ioremap memory\n");
		return -EADDRNOTAVAIL;
	}

	data->soc = (enum soc_type)of_device_get_match_data(&pdev->dev);

	switch (data->soc) {
	case SOC_ARCH_EXYNOS4210:
		data->tmu_set_trip_temp = exynos4210_tmu_set_trip_temp;
		data->tmu_set_trip_hyst = exynos4210_tmu_set_trip_hyst;
		data->tmu_initialize = exynos4210_tmu_initialize;
		data->tmu_control = exynos4210_tmu_control;
		data->tmu_read = exynos4210_tmu_read;
		data->tmu_clear_irqs = exynos4210_tmu_clear_irqs;
		data->ntrip = 4;
		data->gain = 15;
		data->reference_voltage = 7;
		data->efuse_value = 55;
		data->min_efuse_value = 40;
		data->max_efuse_value = 100;
		break;
	case SOC_ARCH_EXYNOS3250:
	case SOC_ARCH_EXYNOS4412:
	case SOC_ARCH_EXYNOS5250:
	case SOC_ARCH_EXYNOS5260:
	case SOC_ARCH_EXYNOS5420:
	case SOC_ARCH_EXYNOS5420_TRIMINFO:
		data->tmu_set_trip_temp = exynos4412_tmu_set_trip_temp;
		data->tmu_set_trip_hyst = exynos4412_tmu_set_trip_hyst;
		data->tmu_initialize = exynos4412_tmu_initialize;
		data->tmu_control = exynos4210_tmu_control;
		data->tmu_read = exynos4412_tmu_read;
		data->tmu_set_emulation = exynos4412_tmu_set_emulation;
		data->tmu_clear_irqs = exynos4210_tmu_clear_irqs;
		data->ntrip = 4;
		data->gain = 8;
		data->reference_voltage = 16;
		data->efuse_value = 55;
		if (data->soc != SOC_ARCH_EXYNOS5420 &&
		    data->soc != SOC_ARCH_EXYNOS5420_TRIMINFO)
			data->min_efuse_value = 40;
		else
			data->min_efuse_value = 0;
		data->max_efuse_value = 100;
		break;
	case SOC_ARCH_EXYNOS5433:
		data->tmu_set_trip_temp = exynos5433_tmu_set_trip_temp;
		data->tmu_set_trip_hyst = exynos5433_tmu_set_trip_hyst;
		data->tmu_initialize = exynos5433_tmu_initialize;
		data->tmu_control = exynos5433_tmu_control;
		data->tmu_read = exynos4412_tmu_read;
		data->tmu_set_emulation = exynos4412_tmu_set_emulation;
		data->tmu_clear_irqs = exynos4210_tmu_clear_irqs;
		data->ntrip = 8;
		data->gain = 8;
		if (res.start == EXYNOS5433_G3D_BASE)
			data->reference_voltage = 23;
		else
			data->reference_voltage = 16;
		data->efuse_value = 75;
		data->min_efuse_value = 40;
		data->max_efuse_value = 150;
		break;
	case SOC_ARCH_EXYNOS7:
		data->tmu_set_trip_temp = exynos7_tmu_set_trip_temp;
		data->tmu_set_trip_hyst = exynos7_tmu_set_trip_hyst;
		data->tmu_initialize = exynos7_tmu_initialize;
		data->tmu_control = exynos7_tmu_control;
		data->tmu_read = exynos7_tmu_read;
		data->tmu_set_emulation = exynos4412_tmu_set_emulation;
		data->tmu_clear_irqs = exynos4210_tmu_clear_irqs;
		data->ntrip = 8;
		data->gain = 9;
		data->reference_voltage = 17;
		data->efuse_value = 75;
		data->min_efuse_value = 15;
		data->max_efuse_value = 100;
		break;
	default:
		dev_err(&pdev->dev, "Platform not supported\n");
		return -EINVAL;
	}

	data->cal_type = TYPE_ONE_POINT_TRIMMING;

	/*
	 * Check if the TMU shares some registers and then try to map the
	 * memory of common registers.
	 */
	if (data->soc != SOC_ARCH_EXYNOS5420_TRIMINFO)
		return 0;

	if (of_address_to_resource(pdev->dev.of_node, 1, &res)) {
		dev_err(&pdev->dev, "failed to get Resource 1\n");
		return -ENODEV;
	}

	data->base_second = devm_ioremap(&pdev->dev, res.start,
					resource_size(&res));
	if (!data->base_second) {
		dev_err(&pdev->dev, "Failed to ioremap memory\n");
		return -ENOMEM;
	}

	return 0;
}