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
struct platform_device {int dummy; } ;
struct of_regulator_match {int dummy; } ;
struct da9063_regulators_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct da9063_regulators_pdata* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct da9063_regulators_pdata *da9063_parse_regulators_dt(
		struct platform_device *pdev,
		struct of_regulator_match **da9063_reg_matches)
{
	*da9063_reg_matches = NULL;
	return ERR_PTR(-ENODEV);
}