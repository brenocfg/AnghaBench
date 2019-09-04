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
struct arizona_ldo1 {int /*<<< orphan*/  init_data; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  ldo1; } ;
struct arizona {int type; int external_dcvdd; TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM1814 133 
#define  WM5102 132 
#define  WM5110 131 
#define  WM8280 130 
#define  WM8997 129 
#define  WM8998 128 
 struct regulator_desc arizona_ldo1 ; 
 int arizona_ldo1_common_init (struct platform_device*,struct arizona_ldo1*,struct regulator_desc const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  arizona_ldo1_default ; 
 int /*<<< orphan*/  arizona_ldo1_dvfs ; 
 struct regulator_desc arizona_ldo1_hc ; 
 int /*<<< orphan*/  arizona_ldo1_wm5110 ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arizona_ldo1* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_ldo1_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct arizona_ldo1 *ldo1;
	const struct regulator_desc *desc;
	bool external_dcvdd;
	int ret;

	ldo1 = devm_kzalloc(&pdev->dev, sizeof(*ldo1), GFP_KERNEL);
	if (!ldo1)
		return -ENOMEM;

	ldo1->regmap = arizona->regmap;

	/*
	 * Since the chip usually supplies itself we provide some
	 * default init_data for it.  This will be overridden with
	 * platform data if provided.
	 */
	switch (arizona->type) {
	case WM5102:
	case WM8997:
	case WM8998:
	case WM1814:
		desc = &arizona_ldo1_hc;
		ldo1->init_data = arizona_ldo1_dvfs;
		break;
	case WM5110:
	case WM8280:
		desc = &arizona_ldo1;
		ldo1->init_data = arizona_ldo1_wm5110;
		break;
	default:
		desc = &arizona_ldo1;
		ldo1->init_data = arizona_ldo1_default;
		break;
	}

	ret = arizona_ldo1_common_init(pdev, ldo1, desc,
				       &arizona->pdata.ldo1,
				       &external_dcvdd);
	if (ret == 0)
		arizona->external_dcvdd = external_dcvdd;

	return ret;
}