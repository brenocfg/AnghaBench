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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ath10k_snoc {TYPE_1__* ce_irqs; struct platform_device* dev; int /*<<< orphan*/  mem_pa; int /*<<< orphan*/  mem; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_line; } ;

/* Variables and functions */
 int CE_COUNT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ath10k_snoc_resource_init(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct platform_device *pdev;
	struct resource *res;
	int i, ret = 0;

	pdev = ar_snoc->dev;
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "membase");
	if (!res) {
		ath10k_err(ar, "Memory base not found in DT\n");
		return -EINVAL;
	}

	ar_snoc->mem_pa = res->start;
	ar_snoc->mem = devm_ioremap(&pdev->dev, ar_snoc->mem_pa,
				    resource_size(res));
	if (!ar_snoc->mem) {
		ath10k_err(ar, "Memory base ioremap failed with physical address %pa\n",
			   &ar_snoc->mem_pa);
		return -EINVAL;
	}

	for (i = 0; i < CE_COUNT; i++) {
		res = platform_get_resource(ar_snoc->dev, IORESOURCE_IRQ, i);
		if (!res) {
			ath10k_err(ar, "failed to get IRQ%d\n", i);
			ret = -ENODEV;
			goto out;
		}
		ar_snoc->ce_irqs[i].irq_line = res->start;
	}

out:
	return ret;
}