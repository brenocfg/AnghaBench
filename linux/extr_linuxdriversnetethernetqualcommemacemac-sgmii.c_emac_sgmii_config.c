#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sgmii_ops {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct emac_sgmii {int irq; void* base; void* digital; struct sgmii_ops* sgmii_ops; } ;
struct emac_adapter {struct emac_sgmii phy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct device* device_find_child (TYPE_1__*,struct sgmii_ops**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_sgmii_acpi_match ; 
 int /*<<< orphan*/  emac_sgmii_dt_match ; 
 int emac_sgmii_init (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_link_init (struct emac_adapter*) ; 
 scalar_t__ has_acpi_companion (TYPE_1__*) ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int emac_sgmii_config(struct platform_device *pdev, struct emac_adapter *adpt)
{
	struct platform_device *sgmii_pdev = NULL;
	struct emac_sgmii *phy = &adpt->phy;
	struct resource *res;
	int ret;

	if (has_acpi_companion(&pdev->dev)) {
		struct device *dev;

		dev = device_find_child(&pdev->dev, &phy->sgmii_ops,
					emac_sgmii_acpi_match);

		if (!dev) {
			dev_warn(&pdev->dev, "cannot find internal phy node\n");
			return 0;
		}

		sgmii_pdev = to_platform_device(dev);
	} else {
		const struct of_device_id *match;
		struct device_node *np;

		np = of_parse_phandle(pdev->dev.of_node, "internal-phy", 0);
		if (!np) {
			dev_err(&pdev->dev, "missing internal-phy property\n");
			return -ENODEV;
		}

		sgmii_pdev = of_find_device_by_node(np);
		of_node_put(np);
		if (!sgmii_pdev) {
			dev_err(&pdev->dev, "invalid internal-phy property\n");
			return -ENODEV;
		}

		match = of_match_device(emac_sgmii_dt_match, &sgmii_pdev->dev);
		if (!match) {
			dev_err(&pdev->dev, "unrecognized internal phy node\n");
			ret = -ENODEV;
			goto error_put_device;
		}

		phy->sgmii_ops = (struct sgmii_ops *)match->data;
	}

	/* Base address is the first address */
	res = platform_get_resource(sgmii_pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -EINVAL;
		goto error_put_device;
	}

	phy->base = ioremap(res->start, resource_size(res));
	if (!phy->base) {
		ret = -ENOMEM;
		goto error_put_device;
	}

	/* v2 SGMII has a per-lane digital digital, so parse it if it exists */
	res = platform_get_resource(sgmii_pdev, IORESOURCE_MEM, 1);
	if (res) {
		phy->digital = ioremap(res->start, resource_size(res));
		if (!phy->digital) {
			ret = -ENOMEM;
			goto error_unmap_base;
		}
	}

	ret = emac_sgmii_init(adpt);
	if (ret)
		goto error;

	emac_sgmii_link_init(adpt);

	ret = platform_get_irq(sgmii_pdev, 0);
	if (ret > 0)
		phy->irq = ret;

	/* We've remapped the addresses, so we don't need the device any
	 * more.  of_find_device_by_node() says we should release it.
	 */
	put_device(&sgmii_pdev->dev);

	return 0;

error:
	if (phy->digital)
		iounmap(phy->digital);
error_unmap_base:
	iounmap(phy->base);
error_put_device:
	put_device(&sgmii_pdev->dev);

	return ret;
}