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
struct qcom_pcie_resources_1_0_0 {int /*<<< orphan*/  vdda; int /*<<< orphan*/  aux; int /*<<< orphan*/  iface; int /*<<< orphan*/  master_bus; int /*<<< orphan*/  slave_bus; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {struct qcom_pcie_resources_1_0_0 v1_0_0; } ;
struct qcom_pcie {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_pcie_deinit_1_0_0(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_1_0_0 *res = &pcie->res.v1_0_0;

	reset_control_assert(res->core);
	clk_disable_unprepare(res->slave_bus);
	clk_disable_unprepare(res->master_bus);
	clk_disable_unprepare(res->iface);
	clk_disable_unprepare(res->aux);
	regulator_disable(res->vdda);
}