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
struct regmap {int dummy; } ;
struct clcd_board {int dummy; } ;
struct amba_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  PMU_CTRL_LCDNDIF ; 
 int /*<<< orphan*/  PMU_CTRL_OFFSET ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (char*) ; 

int nomadik_clcd_init_board(struct amba_device *adev,
			    struct clcd_board *board)
{
	struct regmap *pmu_regmap;

	dev_info(&adev->dev, "Nomadik CLCD board init\n");
	pmu_regmap =
		syscon_regmap_lookup_by_compatible("stericsson,nomadik-pmu");
	if (IS_ERR(pmu_regmap)) {
		dev_err(&adev->dev, "could not find PMU syscon regmap\n");
		return PTR_ERR(pmu_regmap);
	}
	regmap_update_bits(pmu_regmap,
			   PMU_CTRL_OFFSET,
			   PMU_CTRL_LCDNDIF,
			   0);
	dev_info(&adev->dev, "set PMU mux to CLCD mode\n");

	return 0;
}