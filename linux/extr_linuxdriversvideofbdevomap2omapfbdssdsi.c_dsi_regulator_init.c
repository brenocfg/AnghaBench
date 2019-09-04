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
struct regulator {int dummy; } ;
struct platform_device {int dummy; } ;
struct dsi_data {struct regulator* vdds_dsi_reg; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 

__attribute__((used)) static int dsi_regulator_init(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	struct regulator *vdds_dsi;

	if (dsi->vdds_dsi_reg != NULL)
		return 0;

	vdds_dsi = devm_regulator_get(&dsi->pdev->dev, "vdd");

	if (IS_ERR(vdds_dsi)) {
		if (PTR_ERR(vdds_dsi) != -EPROBE_DEFER)
			DSSERR("can't get DSI VDD regulator\n");
		return PTR_ERR(vdds_dsi);
	}

	dsi->vdds_dsi_reg = vdds_dsi;

	return 0;
}