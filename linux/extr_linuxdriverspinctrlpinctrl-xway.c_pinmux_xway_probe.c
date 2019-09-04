#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_xway_soc {int pin_count; int /*<<< orphan*/  num_exin; int /*<<< orphan*/  exin; int /*<<< orphan*/  num_funcs; int /*<<< orphan*/  funcs; int /*<<< orphan*/  num_grps; int /*<<< orphan*/  grps; int /*<<< orphan*/  mfp; } ;
struct pinctrl_pin_desc {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_13__ {char* name; scalar_t__ number; } ;
struct TYPE_12__ {int ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {int npins; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {int num_pads; int num_mfp; int /*<<< orphan*/  pctrl; int /*<<< orphan*/  num_exin; int /*<<< orphan*/  exin; int /*<<< orphan*/  num_funcs; int /*<<< orphan*/  funcs; int /*<<< orphan*/  num_grps; int /*<<< orphan*/  grps; int /*<<< orphan*/  mfp; TYPE_7__* pads; int /*<<< orphan*/ * membase; } ;
struct TYPE_9__ {int npins; int /*<<< orphan*/  name; TYPE_7__* pins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO0 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct pinctrl_xway_soc danube_pinctrl ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 TYPE_7__* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 char* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ltq_pinctrl_register (struct platform_device*,TYPE_2__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_4__ xway_chip ; 
 TYPE_3__ xway_gpio_range ; 
 TYPE_2__ xway_info ; 
 int /*<<< orphan*/  xway_match ; 
 TYPE_1__ xway_pctrl_desc ; 

__attribute__((used)) static int pinmux_xway_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	const struct pinctrl_xway_soc *xway_soc;
	struct resource *res;
	int ret, i;

	/* get and remap our register range */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xway_info.membase[0] = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xway_info.membase[0]))
		return PTR_ERR(xway_info.membase[0]);

	match = of_match_device(xway_match, &pdev->dev);
	if (match)
		xway_soc = (const struct pinctrl_xway_soc *) match->data;
	else
		xway_soc = &danube_pinctrl;

	/* find out how many pads we have */
	xway_chip.ngpio = xway_soc->pin_count;

	/* load our pad descriptors */
	xway_info.pads = devm_kcalloc(&pdev->dev,
			xway_chip.ngpio, sizeof(struct pinctrl_pin_desc),
			GFP_KERNEL);
	if (!xway_info.pads)
		return -ENOMEM;

	for (i = 0; i < xway_chip.ngpio; i++) {
		/* strlen("ioXY") + 1 = 5 */
		char *name = devm_kzalloc(&pdev->dev, 5, GFP_KERNEL);

		if (!name)
			return -ENOMEM;

		snprintf(name, 5, "io%d", i);
		xway_info.pads[i].number = GPIO0 + i;
		xway_info.pads[i].name = name;
	}
	xway_pctrl_desc.pins = xway_info.pads;

	/* register the gpio chip */
	xway_chip.parent = &pdev->dev;
	ret = devm_gpiochip_add_data(&pdev->dev, &xway_chip, NULL);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register gpio chip\n");
		return ret;
	}

	/* setup the data needed by pinctrl */
	xway_pctrl_desc.name	= dev_name(&pdev->dev);
	xway_pctrl_desc.npins	= xway_chip.ngpio;

	xway_info.num_pads	= xway_chip.ngpio;
	xway_info.num_mfp	= xway_chip.ngpio;
	xway_info.mfp		= xway_soc->mfp;
	xway_info.grps		= xway_soc->grps;
	xway_info.num_grps	= xway_soc->num_grps;
	xway_info.funcs		= xway_soc->funcs;
	xway_info.num_funcs	= xway_soc->num_funcs;
	xway_info.exin		= xway_soc->exin;
	xway_info.num_exin	= xway_soc->num_exin;

	/* register with the generic lantiq layer */
	ret = ltq_pinctrl_register(pdev, &xway_info);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register pinctrl driver\n");
		return ret;
	}

	/* finish with registering the gpio range in pinctrl */
	xway_gpio_range.npins = xway_chip.ngpio;
	xway_gpio_range.base = xway_chip.base;
	pinctrl_add_gpio_range(xway_info.pctrl, &xway_gpio_range);
	dev_info(&pdev->dev, "Init done\n");
	return 0;
}