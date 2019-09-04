#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qcom_pcie_resources_2_3_2 {void* pipe_clk; void* slave_clk; void* master_clk; void* cfg_clk; void* aux_clk; TYPE_2__* supplies; } ;
struct TYPE_4__ {struct qcom_pcie_resources_2_3_2 v2_3_2; } ;
struct qcom_pcie {struct dw_pcie* pci; TYPE_1__ res; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int qcom_pcie_get_resources_2_3_2(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;
	struct dw_pcie *pci = pcie->pci;
	struct device *dev = pci->dev;
	int ret;

	res->supplies[0].supply = "vdda";
	res->supplies[1].supply = "vddpe-3v3";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(res->supplies),
				      res->supplies);
	if (ret)
		return ret;

	res->aux_clk = devm_clk_get(dev, "aux");
	if (IS_ERR(res->aux_clk))
		return PTR_ERR(res->aux_clk);

	res->cfg_clk = devm_clk_get(dev, "cfg");
	if (IS_ERR(res->cfg_clk))
		return PTR_ERR(res->cfg_clk);

	res->master_clk = devm_clk_get(dev, "bus_master");
	if (IS_ERR(res->master_clk))
		return PTR_ERR(res->master_clk);

	res->slave_clk = devm_clk_get(dev, "bus_slave");
	if (IS_ERR(res->slave_clk))
		return PTR_ERR(res->slave_clk);

	res->pipe_clk = devm_clk_get(dev, "pipe");
	return PTR_ERR_OR_ZERO(res->pipe_clk);
}