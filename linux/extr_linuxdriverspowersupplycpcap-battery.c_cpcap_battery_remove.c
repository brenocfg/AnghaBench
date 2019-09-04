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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cpcap_battery_ddata {int /*<<< orphan*/  reg; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_REG_BPEOL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct cpcap_battery_ddata* platform_get_drvdata (struct platform_device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_battery_remove(struct platform_device *pdev)
{
	struct cpcap_battery_ddata *ddata = platform_get_drvdata(pdev);
	int error;

	atomic_set(&ddata->active, 0);
	error = regmap_update_bits(ddata->reg, CPCAP_REG_BPEOL,
				   0xffff, 0);
	if (error)
		dev_err(&pdev->dev, "could not disable: %i\n", error);

	return 0;
}