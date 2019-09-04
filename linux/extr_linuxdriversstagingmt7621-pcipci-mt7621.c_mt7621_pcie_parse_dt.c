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
struct resource {int dummy; } ;
struct mt7621_pcie {int /*<<< orphan*/  base; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int mt7621_pcie_parse_dt(struct mt7621_pcie *pcie)
{
	struct device *dev = pcie->dev;
	struct device_node *node = dev->of_node;
	struct resource regs;
	const char *type;
	int err;

	type = of_get_property(node, "device_type", NULL);
	if (!type || strcmp(type, "pci") != 0) {
		dev_err(dev, "invalid \"device_type\" %s\n", type);
		return -EINVAL;
	}

	err = of_address_to_resource(node, 0, &regs);
	if (err) {
		dev_err(dev, "missing \"reg\" property\n");
		return err;
	}

	pcie->base = devm_ioremap_resource(dev, &regs);
	if (IS_ERR(pcie->base))
		return PTR_ERR(pcie->base);

	return 0;
}