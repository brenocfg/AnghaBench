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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int fsl_espi_probe (struct device*,struct resource*,unsigned int,unsigned int) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 unsigned int of_fsl_espi_get_chipselects (struct device*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int of_fsl_espi_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *np = ofdev->dev.of_node;
	struct resource mem;
	unsigned int irq, num_cs;
	int ret;

	if (of_property_read_bool(np, "mode")) {
		dev_err(dev, "mode property is not supported on ESPI!\n");
		return -EINVAL;
	}

	num_cs = of_fsl_espi_get_chipselects(dev);
	if (!num_cs)
		return -EINVAL;

	ret = of_address_to_resource(np, 0, &mem);
	if (ret)
		return ret;

	irq = irq_of_parse_and_map(np, 0);
	if (!irq)
		return -EINVAL;

	return fsl_espi_probe(dev, &mem, irq, num_cs);
}