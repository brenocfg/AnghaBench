#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct phy {TYPE_1__ dev; } ;
struct of_phandle_args {int args_count; scalar_t__* args; struct device_node* np; } ;
struct mtk_tphy {int nphys; TYPE_2__* pdata; struct mtk_phy_instance** phys; } ;
struct mtk_phy_instance {scalar_t__ type; struct phy* phy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MTK_PHY_V1 ; 
 scalar_t__ MTK_PHY_V2 ; 
 scalar_t__ PHY_TYPE_PCIE ; 
 scalar_t__ PHY_TYPE_SATA ; 
 scalar_t__ PHY_TYPE_USB2 ; 
 scalar_t__ PHY_TYPE_USB3 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct mtk_tphy* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  phy_parse_property (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  phy_v1_banks_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  phy_v2_banks_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 

__attribute__((used)) static struct phy *mtk_phy_xlate(struct device *dev,
					struct of_phandle_args *args)
{
	struct mtk_tphy *tphy = dev_get_drvdata(dev);
	struct mtk_phy_instance *instance = NULL;
	struct device_node *phy_np = args->np;
	int index;

	if (args->args_count != 1) {
		dev_err(dev, "invalid number of cells in 'phy' property\n");
		return ERR_PTR(-EINVAL);
	}

	for (index = 0; index < tphy->nphys; index++)
		if (phy_np == tphy->phys[index]->phy->dev.of_node) {
			instance = tphy->phys[index];
			break;
		}

	if (!instance) {
		dev_err(dev, "failed to find appropriate phy\n");
		return ERR_PTR(-EINVAL);
	}

	instance->type = args->args[0];
	if (!(instance->type == PHY_TYPE_USB2 ||
	      instance->type == PHY_TYPE_USB3 ||
	      instance->type == PHY_TYPE_PCIE ||
	      instance->type == PHY_TYPE_SATA)) {
		dev_err(dev, "unsupported device type: %d\n", instance->type);
		return ERR_PTR(-EINVAL);
	}

	if (tphy->pdata->version == MTK_PHY_V1) {
		phy_v1_banks_init(tphy, instance);
	} else if (tphy->pdata->version == MTK_PHY_V2) {
		phy_v2_banks_init(tphy, instance);
	} else {
		dev_err(dev, "phy version is not supported\n");
		return ERR_PTR(-EINVAL);
	}

	phy_parse_property(tphy, instance);

	return instance->phy;
}