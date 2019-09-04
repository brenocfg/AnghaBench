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
struct sunxi_priv_data {scalar_t__ regulator; int /*<<< orphan*/  tx_clk; scalar_t__ clk_enabled; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static void sun7i_gmac_exit(struct platform_device *pdev, void *priv)
{
	struct sunxi_priv_data *gmac = priv;

	if (gmac->clk_enabled) {
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	}
	clk_unprepare(gmac->tx_clk);

	if (gmac->regulator)
		regulator_disable(gmac->regulator);
}