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
struct rockchip_usb_phy {scalar_t__ clk; int /*<<< orphan*/  clk480m; int /*<<< orphan*/  np; int /*<<< orphan*/  uart_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_usb_phy_action(void *data)
{
	struct rockchip_usb_phy *rk_phy = data;

	if (!rk_phy->uart_enabled) {
		of_clk_del_provider(rk_phy->np);
		clk_unregister(rk_phy->clk480m);
	}

	if (rk_phy->clk)
		clk_put(rk_phy->clk);
}