#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct arizona_micsupp {int /*<<< orphan*/  init_data; int /*<<< orphan*/  dev; int /*<<< orphan*/ * dapm; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  micvdd; } ;
struct arizona {int type; TYPE_1__ pdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  dapm; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM5110 129 
#define  WM8280 128 
 struct regulator_desc arizona_micsupp ; 
 int arizona_micsupp_common_init (struct platform_device*,struct arizona_micsupp*,struct regulator_desc const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arizona_micsupp_default ; 
 struct regulator_desc arizona_micsupp_ext ; 
 int /*<<< orphan*/  arizona_micsupp_ext_default ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arizona_micsupp* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_micsupp_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	const struct regulator_desc *desc;
	struct arizona_micsupp *micsupp;

	micsupp = devm_kzalloc(&pdev->dev, sizeof(*micsupp), GFP_KERNEL);
	if (!micsupp)
		return -ENOMEM;

	micsupp->regmap = arizona->regmap;
	micsupp->dapm = &arizona->dapm;
	micsupp->dev = arizona->dev;

	/*
	 * Since the chip usually supplies itself we provide some
	 * default init_data for it.  This will be overridden with
	 * platform data if provided.
	 */
	switch (arizona->type) {
	case WM5110:
	case WM8280:
		desc = &arizona_micsupp_ext;
		micsupp->init_data = arizona_micsupp_ext_default;
		break;
	default:
		desc = &arizona_micsupp;
		micsupp->init_data = arizona_micsupp_default;
		break;
	}

	return arizona_micsupp_common_init(pdev, micsupp, desc,
					   &arizona->pdata.micvdd);
}