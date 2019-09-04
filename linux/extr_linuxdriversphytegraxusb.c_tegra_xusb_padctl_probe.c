#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tegra_xusb_padctl_soc {TYPE_1__* ops; } ;
struct tegra_xusb_padctl {struct tegra_xusb_padctl* rst; struct tegra_xusb_padctl* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  pads; int /*<<< orphan*/  lanes; int /*<<< orphan*/  ports; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct tegra_xusb_padctl_soc* data; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* remove ) (struct tegra_xusb_padctl*) ;struct tegra_xusb_padctl* (* probe ) (TYPE_2__*,struct tegra_xusb_padctl_soc const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct tegra_xusb_padctl*) ; 
 int PTR_ERR (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct tegra_xusb_padctl* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct tegra_xusb_padctl* devm_reset_control_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  reset_control_assert (struct tegra_xusb_padctl*) ; 
 int reset_control_deassert (struct tegra_xusb_padctl*) ; 
 struct tegra_xusb_padctl* stub1 (TYPE_2__*,struct tegra_xusb_padctl_soc const*) ; 
 int /*<<< orphan*/  stub2 (struct tegra_xusb_padctl*) ; 
 int tegra_xusb_padctl_legacy_probe (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_xusb_padctl_of_match ; 
 int /*<<< orphan*/  tegra_xusb_remove_pads (struct tegra_xusb_padctl*) ; 
 int tegra_xusb_setup_pads (struct tegra_xusb_padctl*) ; 
 int tegra_xusb_setup_ports (struct tegra_xusb_padctl*) ; 

__attribute__((used)) static int tegra_xusb_padctl_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct tegra_xusb_padctl_soc *soc;
	struct tegra_xusb_padctl *padctl;
	const struct of_device_id *match;
	struct resource *res;
	int err;

	/* for backwards compatibility with old device trees */
	np = of_get_child_by_name(np, "pads");
	if (!np) {
		dev_warn(&pdev->dev, "deprecated DT, using legacy driver\n");
		return tegra_xusb_padctl_legacy_probe(pdev);
	}

	of_node_put(np);

	match = of_match_node(tegra_xusb_padctl_of_match, pdev->dev.of_node);
	soc = match->data;

	padctl = soc->ops->probe(&pdev->dev, soc);
	if (IS_ERR(padctl))
		return PTR_ERR(padctl);

	platform_set_drvdata(pdev, padctl);
	INIT_LIST_HEAD(&padctl->ports);
	INIT_LIST_HEAD(&padctl->lanes);
	INIT_LIST_HEAD(&padctl->pads);
	mutex_init(&padctl->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	padctl->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(padctl->regs)) {
		err = PTR_ERR(padctl->regs);
		goto remove;
	}

	padctl->rst = devm_reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(padctl->rst)) {
		err = PTR_ERR(padctl->rst);
		goto remove;
	}

	err = reset_control_deassert(padctl->rst);
	if (err < 0)
		goto remove;

	err = tegra_xusb_setup_pads(padctl);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to setup pads: %d\n", err);
		goto reset;
	}

	err = tegra_xusb_setup_ports(padctl);
	if (err) {
		dev_err(&pdev->dev, "failed to setup XUSB ports: %d\n", err);
		goto remove_pads;
	}

	return 0;

remove_pads:
	tegra_xusb_remove_pads(padctl);
reset:
	reset_control_assert(padctl->rst);
remove:
	soc->ops->remove(padctl);
	return err;
}