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
struct q6afe_dai_data {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct q6afe_dai_data*) ; 
 struct q6afe_dai_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_q6afe_parse_dai_data (struct device*,struct q6afe_dai_data*) ; 
 int /*<<< orphan*/  q6afe_dai_component ; 
 int /*<<< orphan*/  q6afe_dais ; 

__attribute__((used)) static int q6afe_dai_dev_probe(struct platform_device *pdev)
{
	struct q6afe_dai_data *dai_data;
	struct device *dev = &pdev->dev;

	dai_data = devm_kzalloc(dev, sizeof(*dai_data), GFP_KERNEL);
	if (!dai_data)
		return -ENOMEM;

	dev_set_drvdata(dev, dai_data);

	of_q6afe_parse_dai_data(dev, dai_data);

	return devm_snd_soc_register_component(dev, &q6afe_dai_component,
					  q6afe_dais, ARRAY_SIZE(q6afe_dais));
}