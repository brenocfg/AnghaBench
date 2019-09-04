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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int irq; } ;
struct emac_adapter {void* base; void* csr; TYPE_1__ irq; struct net_device* netdev; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_get_mac_address (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int emac_probe_resources(struct platform_device *pdev,
				struct emac_adapter *adpt)
{
	struct net_device *netdev = adpt->netdev;
	struct resource *res;
	char maddr[ETH_ALEN];
	int ret = 0;

	/* get mac address */
	if (device_get_mac_address(&pdev->dev, maddr, ETH_ALEN))
		ether_addr_copy(netdev->dev_addr, maddr);
	else
		eth_hw_addr_random(netdev);

	/* Core 0 interrupt */
	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"error: missing core0 irq resource (error=%i)\n", ret);
		return ret;
	}
	adpt->irq.irq = ret;

	/* base register address */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	adpt->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(adpt->base))
		return PTR_ERR(adpt->base);

	/* CSR register address */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	adpt->csr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(adpt->csr))
		return PTR_ERR(adpt->csr);

	netdev->base_addr = (unsigned long)adpt->base;

	return 0;
}