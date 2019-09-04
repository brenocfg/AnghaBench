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
struct smbb_charger {scalar_t__ addr; int /*<<< orphan*/  regmap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_EN ; 
 scalar_t__ SMBB_CHG_CTRL ; 
 struct smbb_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smbb_charger_remove(struct platform_device *pdev)
{
	struct smbb_charger *chg;

	chg = platform_get_drvdata(pdev);

	regmap_update_bits(chg->regmap, chg->addr + SMBB_CHG_CTRL, CTRL_EN, 0);

	return 0;
}