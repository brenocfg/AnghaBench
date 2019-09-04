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
struct rockchip_usb2phy {int /*<<< orphan*/  clk480m; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_usb2phy_clk480m_unregister(void *data)
{
	struct rockchip_usb2phy *rphy = data;

	of_clk_del_provider(rphy->dev->of_node);
	clk_unregister(rphy->clk480m);
}