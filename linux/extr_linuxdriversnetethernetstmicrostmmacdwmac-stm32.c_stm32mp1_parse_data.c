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
struct stm32_dwmac {void* syscfg_clk; void* clk_ethstp; void* clk_eth_ck; int /*<<< orphan*/  int_phyclk; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int stm32mp1_parse_data(struct stm32_dwmac *dwmac,
			       struct device *dev)
{
	struct device_node *np = dev->of_node;

	dwmac->int_phyclk = of_property_read_bool(np, "st,int-phyclk");

	/* Check if internal clk from RCC selected */
	if (dwmac->int_phyclk) {
		/*  Get ETH_CLK clocks */
		dwmac->clk_eth_ck = devm_clk_get(dev, "eth-ck");
		if (IS_ERR(dwmac->clk_eth_ck)) {
			dev_err(dev, "No ETH CK clock provided...\n");
			return PTR_ERR(dwmac->clk_eth_ck);
		}
	}

	/*  Clock used for low power mode */
	dwmac->clk_ethstp = devm_clk_get(dev, "ethstp");
	if (IS_ERR(dwmac->clk_ethstp)) {
		dev_err(dev, "No ETH peripheral clock provided for CStop mode ...\n");
		return PTR_ERR(dwmac->clk_ethstp);
	}

	/*  Clock for sysconfig */
	dwmac->syscfg_clk = devm_clk_get(dev, "syscfg-clk");
	if (IS_ERR(dwmac->syscfg_clk)) {
		dev_err(dev, "No syscfg clock provided...\n");
		return PTR_ERR(dwmac->syscfg_clk);
	}

	return 0;
}