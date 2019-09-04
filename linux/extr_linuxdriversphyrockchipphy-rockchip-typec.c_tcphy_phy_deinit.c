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
struct rockchip_typec_phy {int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  clk_core; int /*<<< orphan*/  pipe_rst; int /*<<< orphan*/  uphy_rst; int /*<<< orphan*/  tcphy_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcphy_phy_deinit(struct rockchip_typec_phy *tcphy)
{
	reset_control_assert(tcphy->tcphy_rst);
	reset_control_assert(tcphy->uphy_rst);
	reset_control_assert(tcphy->pipe_rst);
	clk_disable_unprepare(tcphy->clk_core);
	clk_disable_unprepare(tcphy->clk_ref);
}