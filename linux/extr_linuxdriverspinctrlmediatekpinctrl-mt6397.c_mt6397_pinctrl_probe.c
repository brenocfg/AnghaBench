#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mt6397_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 struct mt6397_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt6397_pinctrl_data ; 
 int mtk_pctrl_init (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt6397_pinctrl_probe(struct platform_device *pdev)
{
	struct mt6397_chip *mt6397;

	mt6397 = dev_get_drvdata(pdev->dev.parent);
	return mtk_pctrl_init(pdev, &mt6397_pinctrl_data, mt6397->regmap);
}