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
struct wiznet_platform_data {void* mac_addr; int /*<<< orphan*/  link_gpio; } ;
struct w5100_ops {int dummy; } ;
struct w5100_mmio_priv {int dummy; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ W5100_BUS_DIRECT_SIZE ; 
 struct wiznet_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_ether_addr (void*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_size (struct resource*) ; 
 struct w5100_ops w5100_mmio_direct_ops ; 
 struct w5100_ops w5100_mmio_indirect_ops ; 
 int w5100_probe (int /*<<< orphan*/ *,struct w5100_ops const*,int,void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w5100_mmio_probe(struct platform_device *pdev)
{
	struct wiznet_platform_data *data = dev_get_platdata(&pdev->dev);
	const void *mac_addr = NULL;
	struct resource *mem;
	const struct w5100_ops *ops;
	int irq;

	if (data && is_valid_ether_addr(data->mac_addr))
		mac_addr = data->mac_addr;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (resource_size(mem) < W5100_BUS_DIRECT_SIZE)
		ops = &w5100_mmio_indirect_ops;
	else
		ops = &w5100_mmio_direct_ops;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	return w5100_probe(&pdev->dev, ops, sizeof(struct w5100_mmio_priv),
			   mac_addr, irq, data ? data->link_gpio : -EINVAL);
}