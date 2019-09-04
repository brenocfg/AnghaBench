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
struct sunxi_priv_data {int internal_phy_powered; int /*<<< orphan*/  rst_ephy; int /*<<< orphan*/  ephy_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_dwmac_unpower_internal_phy(struct sunxi_priv_data *gmac)
{
	if (!gmac->internal_phy_powered)
		return 0;

	clk_disable_unprepare(gmac->ephy_clk);
	reset_control_assert(gmac->rst_ephy);
	gmac->internal_phy_powered = false;
	return 0;
}