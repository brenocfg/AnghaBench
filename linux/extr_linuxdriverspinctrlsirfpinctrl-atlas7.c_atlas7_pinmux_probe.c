#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct atlas7_pmx {int /*<<< orphan*/ * regs; int /*<<< orphan*/  pctl; TYPE_1__ pctl_desc; TYPE_7__* pctl_data; TYPE_2__* dev; int /*<<< orphan*/  sys2pci_base; } ;
struct TYPE_10__ {int /*<<< orphan*/  pads_cnt; int /*<<< orphan*/  pads; } ;

/* Variables and functions */
 int ATLAS7_PINCTRL_REG_BANKS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_7__ atlas7_ioc_data ; 
 int /*<<< orphan*/  atlas7_pinconf_ops ; 
 int /*<<< orphan*/  atlas7_pinctrl_ops ; 
 int /*<<< orphan*/  atlas7_pinmux_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct atlas7_pmx* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pinctrl_register (TYPE_1__*,TYPE_2__*,struct atlas7_pmx*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atlas7_pmx*) ; 

__attribute__((used)) static int atlas7_pinmux_probe(struct platform_device *pdev)
{
	int ret, idx;
	struct atlas7_pmx *pmx;
	struct device_node *np = pdev->dev.of_node;
	u32 banks = ATLAS7_PINCTRL_REG_BANKS;
	struct device_node *sys2pci_np;
	struct resource res;

	/* Create state holders etc for this driver */
	pmx = devm_kzalloc(&pdev->dev, sizeof(*pmx), GFP_KERNEL);
	if (!pmx)
		return -ENOMEM;

	/* The sd3 and sd9 shared all pins, and the function select by
	 * SYS2PCI_SDIO9SEL register
	 */
	sys2pci_np = of_find_node_by_name(NULL, "sys2pci");
	if (!sys2pci_np)
		return -EINVAL;

	ret = of_address_to_resource(sys2pci_np, 0, &res);
	of_node_put(sys2pci_np);
	if (ret)
		return ret;

	pmx->sys2pci_base = devm_ioremap_resource(&pdev->dev, &res);
	if (IS_ERR(pmx->sys2pci_base))
		return -ENOMEM;

	pmx->dev = &pdev->dev;

	pmx->pctl_data = &atlas7_ioc_data;
	pmx->pctl_desc.name = "pinctrl-atlas7";
	pmx->pctl_desc.pins = pmx->pctl_data->pads;
	pmx->pctl_desc.npins = pmx->pctl_data->pads_cnt;
	pmx->pctl_desc.pctlops = &atlas7_pinctrl_ops;
	pmx->pctl_desc.pmxops = &atlas7_pinmux_ops;
	pmx->pctl_desc.confops = &atlas7_pinconf_ops;

	for (idx = 0; idx < banks; idx++) {
		pmx->regs[idx] = of_iomap(np, idx);
		if (!pmx->regs[idx]) {
			dev_err(&pdev->dev,
				"can't map ioc bank#%d registers\n", idx);
			ret = -ENOMEM;
			goto unmap_io;
		}
	}

	/* Now register the pin controller and all pins it handles */
	pmx->pctl = pinctrl_register(&pmx->pctl_desc, &pdev->dev, pmx);
	if (IS_ERR(pmx->pctl)) {
		dev_err(&pdev->dev, "could not register atlas7 pinmux driver\n");
		ret = PTR_ERR(pmx->pctl);
		goto unmap_io;
	}

	platform_set_drvdata(pdev, pmx);

	dev_info(&pdev->dev, "initialized atlas7 pinmux driver\n");

	return 0;

unmap_io:
	for (idx = 0; idx < banks; idx++) {
		if (!pmx->regs[idx])
			break;
		iounmap(pmx->regs[idx]);
	}

	return ret;
}