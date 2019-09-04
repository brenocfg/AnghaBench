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
struct exynos_tmu_data {int soc; int irq; void* regulator; void* clk_sec; void* clk; void* sclk; void* tzd; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SOC_ARCH_EXYNOS5420_TRIMINFO ; 
#define  SOC_ARCH_EXYNOS5433 129 
#define  SOC_ARCH_EXYNOS7 128 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  clk_unprepare (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct exynos_tmu_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct exynos_tmu_data*) ; 
 int exynos_map_dt_data (struct platform_device*) ; 
 int /*<<< orphan*/  exynos_sensor_ops ; 
 int /*<<< orphan*/  exynos_tmu_control (struct platform_device*,int) ; 
 int exynos_tmu_initialize (struct platform_device*) ; 
 int /*<<< orphan*/  exynos_tmu_irq ; 
 int /*<<< orphan*/  exynos_tmu_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_tmu_data*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 void* thermal_zone_of_sensor_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct exynos_tmu_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int exynos_tmu_probe(struct platform_device *pdev)
{
	struct exynos_tmu_data *data;
	int ret;

	data = devm_kzalloc(&pdev->dev, sizeof(struct exynos_tmu_data),
					GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);
	mutex_init(&data->lock);

	/*
	 * Try enabling the regulator if found
	 * TODO: Add regulator as an SOC feature, so that regulator enable
	 * is a compulsory call.
	 */
	data->regulator = devm_regulator_get_optional(&pdev->dev, "vtmu");
	if (!IS_ERR(data->regulator)) {
		ret = regulator_enable(data->regulator);
		if (ret) {
			dev_err(&pdev->dev, "failed to enable vtmu\n");
			return ret;
		}
	} else {
		if (PTR_ERR(data->regulator) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_info(&pdev->dev, "Regulator node (vtmu) not found\n");
	}

	ret = exynos_map_dt_data(pdev);
	if (ret)
		goto err_sensor;

	INIT_WORK(&data->irq_work, exynos_tmu_work);

	data->clk = devm_clk_get(&pdev->dev, "tmu_apbif");
	if (IS_ERR(data->clk)) {
		dev_err(&pdev->dev, "Failed to get clock\n");
		ret = PTR_ERR(data->clk);
		goto err_sensor;
	}

	data->clk_sec = devm_clk_get(&pdev->dev, "tmu_triminfo_apbif");
	if (IS_ERR(data->clk_sec)) {
		if (data->soc == SOC_ARCH_EXYNOS5420_TRIMINFO) {
			dev_err(&pdev->dev, "Failed to get triminfo clock\n");
			ret = PTR_ERR(data->clk_sec);
			goto err_sensor;
		}
	} else {
		ret = clk_prepare(data->clk_sec);
		if (ret) {
			dev_err(&pdev->dev, "Failed to get clock\n");
			goto err_sensor;
		}
	}

	ret = clk_prepare(data->clk);
	if (ret) {
		dev_err(&pdev->dev, "Failed to get clock\n");
		goto err_clk_sec;
	}

	switch (data->soc) {
	case SOC_ARCH_EXYNOS5433:
	case SOC_ARCH_EXYNOS7:
		data->sclk = devm_clk_get(&pdev->dev, "tmu_sclk");
		if (IS_ERR(data->sclk)) {
			dev_err(&pdev->dev, "Failed to get sclk\n");
			goto err_clk;
		} else {
			ret = clk_prepare_enable(data->sclk);
			if (ret) {
				dev_err(&pdev->dev, "Failed to enable sclk\n");
				goto err_clk;
			}
		}
		break;
	default:
		break;
	}

	/*
	 * data->tzd must be registered before calling exynos_tmu_initialize(),
	 * requesting irq and calling exynos_tmu_control().
	 */
	data->tzd = thermal_zone_of_sensor_register(&pdev->dev, 0, data,
						    &exynos_sensor_ops);
	if (IS_ERR(data->tzd)) {
		ret = PTR_ERR(data->tzd);
		dev_err(&pdev->dev, "Failed to register sensor: %d\n", ret);
		goto err_sclk;
	}

	ret = exynos_tmu_initialize(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to initialize TMU\n");
		goto err_thermal;
	}

	ret = devm_request_irq(&pdev->dev, data->irq, exynos_tmu_irq,
		IRQF_TRIGGER_RISING | IRQF_SHARED, dev_name(&pdev->dev), data);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq: %d\n", data->irq);
		goto err_thermal;
	}

	exynos_tmu_control(pdev, true);
	return 0;

err_thermal:
	thermal_zone_of_sensor_unregister(&pdev->dev, data->tzd);
err_sclk:
	clk_disable_unprepare(data->sclk);
err_clk:
	clk_unprepare(data->clk);
err_clk_sec:
	if (!IS_ERR(data->clk_sec))
		clk_unprepare(data->clk_sec);
err_sensor:
	if (!IS_ERR(data->regulator))
		regulator_disable(data->regulator);

	return ret;
}