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
struct exynos_pcie {int /*<<< orphan*/  reset_gpio; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void exynos_pcie_assert_reset(struct exynos_pcie *ep)
{
	struct dw_pcie *pci = ep->pci;
	struct device *dev = pci->dev;

	if (ep->reset_gpio >= 0)
		devm_gpio_request_one(dev, ep->reset_gpio,
				GPIOF_OUT_INIT_HIGH, "RESET");
}