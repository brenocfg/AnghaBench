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
struct qmp_phy {int index; struct qcom_qmp* qmp; struct phy* phy; struct phy* lane_rst; struct phy* pipe_clk; void* pcs_misc; void* pcs; void* rx; void* tx; } ;
struct qcom_qmp {struct qmp_phy** phys; TYPE_1__* cfg; } ;
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  prop_name ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ has_lane_rst; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int MAX_PROP_NAME ; 
 scalar_t__ PHY_TYPE_PCIE ; 
 scalar_t__ PHY_TYPE_USB3 ; 
 int PTR_ERR (struct phy*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct qcom_qmp* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*) ; 
 struct qmp_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 struct phy* of_clk_get_by_name (struct device_node*,char*) ; 
 void* of_iomap (struct device_node*,int) ; 
 struct phy* of_reset_control_get (struct device_node*,char*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct qmp_phy*) ; 
 int /*<<< orphan*/  qcom_qmp_phy_gen_ops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static
int qcom_qmp_phy_create(struct device *dev, struct device_node *np, int id)
{
	struct qcom_qmp *qmp = dev_get_drvdata(dev);
	struct phy *generic_phy;
	struct qmp_phy *qphy;
	char prop_name[MAX_PROP_NAME];
	int ret;

	qphy = devm_kzalloc(dev, sizeof(*qphy), GFP_KERNEL);
	if (!qphy)
		return -ENOMEM;

	/*
	 * Get memory resources for each phy lane:
	 * Resources are indexed as: tx -> 0; rx -> 1; pcs -> 2; and
	 * pcs_misc (optional) -> 3.
	 */
	qphy->tx = of_iomap(np, 0);
	if (!qphy->tx)
		return -ENOMEM;

	qphy->rx = of_iomap(np, 1);
	if (!qphy->rx)
		return -ENOMEM;

	qphy->pcs = of_iomap(np, 2);
	if (!qphy->pcs)
		return -ENOMEM;

	qphy->pcs_misc = of_iomap(np, 3);
	if (!qphy->pcs_misc)
		dev_vdbg(dev, "PHY pcs_misc-reg not used\n");

	/*
	 * Get PHY's Pipe clock, if any. USB3 and PCIe are PIPE3
	 * based phys, so they essentially have pipe clock. So,
	 * we return error in case phy is USB3 or PIPE type.
	 * Otherwise, we initialize pipe clock to NULL for
	 * all phys that don't need this.
	 */
	snprintf(prop_name, sizeof(prop_name), "pipe%d", id);
	qphy->pipe_clk = of_clk_get_by_name(np, prop_name);
	if (IS_ERR(qphy->pipe_clk)) {
		if (qmp->cfg->type == PHY_TYPE_PCIE ||
		    qmp->cfg->type == PHY_TYPE_USB3) {
			ret = PTR_ERR(qphy->pipe_clk);
			if (ret != -EPROBE_DEFER)
				dev_err(dev,
					"failed to get lane%d pipe_clk, %d\n",
					id, ret);
			return ret;
		}
		qphy->pipe_clk = NULL;
	}

	/* Get lane reset, if any */
	if (qmp->cfg->has_lane_rst) {
		snprintf(prop_name, sizeof(prop_name), "lane%d", id);
		qphy->lane_rst = of_reset_control_get(np, prop_name);
		if (IS_ERR(qphy->lane_rst)) {
			dev_err(dev, "failed to get lane%d reset\n", id);
			return PTR_ERR(qphy->lane_rst);
		}
	}

	generic_phy = devm_phy_create(dev, np, &qcom_qmp_phy_gen_ops);
	if (IS_ERR(generic_phy)) {
		ret = PTR_ERR(generic_phy);
		dev_err(dev, "failed to create qphy %d\n", ret);
		return ret;
	}

	qphy->phy = generic_phy;
	qphy->index = id;
	qphy->qmp = qmp;
	qmp->phys[id] = qphy;
	phy_set_drvdata(generic_phy, qphy);

	return 0;
}