#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct regulator_bulk_data {int dummy; } ;
struct qcom_wcnss {int dummy; } ;
struct qcom_iris {int num_vregs; TYPE_4__* vregs; int /*<<< orphan*/  xo_clk; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct iris_data {int num_vregs; int /*<<< orphan*/  use_48mhz_xo; TYPE_1__* vregs; } ;
struct TYPE_12__ {int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;
struct TYPE_10__ {scalar_t__ load_uA; scalar_t__ max_voltage; int /*<<< orphan*/  min_voltage; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct qcom_wcnss* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 TYPE_4__* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct qcom_iris* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (TYPE_2__*,int,TYPE_4__*) ; 
 struct iris_data* of_device_get_match_data (TYPE_2__*) ; 
 int /*<<< orphan*/  qcom_wcnss_assign_iris (struct qcom_wcnss*,struct qcom_iris*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_load (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regulator_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qcom_iris_probe(struct platform_device *pdev)
{
	const struct iris_data *data;
	struct qcom_wcnss *wcnss;
	struct qcom_iris *iris;
	int ret;
	int i;

	iris = devm_kzalloc(&pdev->dev, sizeof(struct qcom_iris), GFP_KERNEL);
	if (!iris)
		return -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);
	wcnss = dev_get_drvdata(pdev->dev.parent);

	iris->xo_clk = devm_clk_get(&pdev->dev, "xo");
	if (IS_ERR(iris->xo_clk)) {
		if (PTR_ERR(iris->xo_clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to acquire xo clk\n");
		return PTR_ERR(iris->xo_clk);
	}

	iris->num_vregs = data->num_vregs;
	iris->vregs = devm_kcalloc(&pdev->dev,
				   iris->num_vregs,
				   sizeof(struct regulator_bulk_data),
				   GFP_KERNEL);
	if (!iris->vregs)
		return -ENOMEM;

	for (i = 0; i < iris->num_vregs; i++)
		iris->vregs[i].supply = data->vregs[i].name;

	ret = devm_regulator_bulk_get(&pdev->dev, iris->num_vregs, iris->vregs);
	if (ret) {
		dev_err(&pdev->dev, "failed to get regulators\n");
		return ret;
	}

	for (i = 0; i < iris->num_vregs; i++) {
		if (data->vregs[i].max_voltage)
			regulator_set_voltage(iris->vregs[i].consumer,
					      data->vregs[i].min_voltage,
					      data->vregs[i].max_voltage);

		if (data->vregs[i].load_uA)
			regulator_set_load(iris->vregs[i].consumer,
					   data->vregs[i].load_uA);
	}

	qcom_wcnss_assign_iris(wcnss, iris, data->use_48mhz_xo);

	return 0;
}