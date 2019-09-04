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
struct spi_master {int dummy; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct spi_master*) ; 
 int PTR_ERR (struct spi_master*) ; 
 int TYPE_FSL ; 
 int fsl_spi_get_type (struct device*) ; 
 struct spi_master* fsl_spi_probe (struct device*,struct resource*,int) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_fsl_spi_free_chipselects (struct device*) ; 
 int of_fsl_spi_get_chipselects (struct device*) ; 
 int of_mpc8xxx_spi_probe (struct platform_device*) ; 

__attribute__((used)) static int of_fsl_spi_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *np = ofdev->dev.of_node;
	struct spi_master *master;
	struct resource mem;
	int irq = 0, type;
	int ret = -ENOMEM;

	ret = of_mpc8xxx_spi_probe(ofdev);
	if (ret)
		return ret;

	type = fsl_spi_get_type(&ofdev->dev);
	if (type == TYPE_FSL) {
		ret = of_fsl_spi_get_chipselects(dev);
		if (ret)
			goto err;
	}

	ret = of_address_to_resource(np, 0, &mem);
	if (ret)
		goto err;

	irq = irq_of_parse_and_map(np, 0);
	if (!irq) {
		ret = -EINVAL;
		goto err;
	}

	master = fsl_spi_probe(dev, &mem, irq);
	if (IS_ERR(master)) {
		ret = PTR_ERR(master);
		goto err;
	}

	return 0;

err:
	irq_dispose_mapping(irq);
	if (type == TYPE_FSL)
		of_fsl_spi_free_chipselects(dev);
	return ret;
}