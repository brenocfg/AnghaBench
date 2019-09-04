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
struct histb_pcie {scalar_t__ vpcie; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  pipe_clk; int /*<<< orphan*/  aux_clk; int /*<<< orphan*/  bus_reset; int /*<<< orphan*/  sys_reset; int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void histb_pcie_host_disable(struct histb_pcie *hipcie)
{
	reset_control_assert(hipcie->soft_reset);
	reset_control_assert(hipcie->sys_reset);
	reset_control_assert(hipcie->bus_reset);

	clk_disable_unprepare(hipcie->aux_clk);
	clk_disable_unprepare(hipcie->pipe_clk);
	clk_disable_unprepare(hipcie->sys_clk);
	clk_disable_unprepare(hipcie->bus_clk);

	if (gpio_is_valid(hipcie->reset_gpio))
		gpio_set_value_cansleep(hipcie->reset_gpio, 0);

	if (hipcie->vpcie)
		regulator_disable(hipcie->vpcie);
}