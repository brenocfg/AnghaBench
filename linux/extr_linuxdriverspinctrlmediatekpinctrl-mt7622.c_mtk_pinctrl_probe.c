#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct mtk_pinctrl {int /*<<< orphan*/  pctrl; TYPE_1__* soc; int /*<<< orphan*/  base; TYPE_2__* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  custom_params; int /*<<< orphan*/  num_custom_params; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct TYPE_10__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct mtk_pinctrl* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_pinctrl_register_and_init (TYPE_2__*,TYPE_3__*,struct mtk_pinctrl*,int /*<<< orphan*/ *) ; 
 int mtk_build_eint (struct mtk_pinctrl*,struct platform_device*) ; 
 int mtk_build_functions (struct mtk_pinctrl*) ; 
 int mtk_build_gpiochip (struct mtk_pinctrl*,int /*<<< orphan*/ ) ; 
 int mtk_build_groups (struct mtk_pinctrl*) ; 
 int /*<<< orphan*/  mtk_custom_bindings ; 
 TYPE_3__ mtk_desc ; 
 int /*<<< orphan*/  mtk_pinctrl_of_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_pinctrl*) ; 

__attribute__((used)) static int mtk_pinctrl_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mtk_pinctrl *hw;
	const struct of_device_id *of_id =
		of_match_device(mtk_pinctrl_of_match, &pdev->dev);
	int err;

	hw = devm_kzalloc(&pdev->dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	hw->soc = of_id->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "missing IO resource\n");
		return -ENXIO;
	}

	hw->dev = &pdev->dev;
	hw->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hw->base))
		return PTR_ERR(hw->base);

	/* Setup pins descriptions per SoC types */
	mtk_desc.pins = hw->soc->pins;
	mtk_desc.npins = hw->soc->npins;
	mtk_desc.num_custom_params = ARRAY_SIZE(mtk_custom_bindings);
	mtk_desc.custom_params = mtk_custom_bindings;
#ifdef CONFIG_DEBUG_FS
	mtk_desc.custom_conf_items = mtk_conf_items;
#endif

	err = devm_pinctrl_register_and_init(&pdev->dev, &mtk_desc, hw,
					     &hw->pctrl);
	if (err)
		return err;

	/* Setup groups descriptions per SoC types */
	err = mtk_build_groups(hw);
	if (err) {
		dev_err(&pdev->dev, "Failed to build groups\n");
		return err;
	}

	/* Setup functions descriptions per SoC types */
	err = mtk_build_functions(hw);
	if (err) {
		dev_err(&pdev->dev, "Failed to build functions\n");
		return err;
	}

	/* For able to make pinctrl_claim_hogs, we must not enable pinctrl
	 * until all groups and functions are being added one.
	 */
	err = pinctrl_enable(hw->pctrl);
	if (err)
		return err;

	err = mtk_build_eint(hw, pdev);
	if (err)
		dev_warn(&pdev->dev,
			 "Failed to add EINT, but pinctrl still can work\n");

	/* Build gpiochip should be after pinctrl_enable is done */
	err = mtk_build_gpiochip(hw, pdev->dev.of_node);
	if (err) {
		dev_err(&pdev->dev, "Failed to add gpio_chip\n");
		return err;
	}

	platform_set_drvdata(pdev, hw);

	return 0;
}