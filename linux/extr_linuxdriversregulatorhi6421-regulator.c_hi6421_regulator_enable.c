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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct regulator_dev {TYPE_1__ dev; } ;
struct hi6421_regulator_pdata {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct hi6421_regulator_pdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_enable_regmap (struct regulator_dev*) ; 

__attribute__((used)) static int hi6421_regulator_enable(struct regulator_dev *rdev)
{
	struct hi6421_regulator_pdata *pdata;

	pdata = dev_get_drvdata(rdev->dev.parent);
	/* hi6421 spec requires regulator enablement must be serialized:
	 *  - Because when BUCK, LDO switching from off to on, it will have
	 *    a huge instantaneous current; so you can not turn on two or
	 *    more LDO or BUCKs simultaneously, or it may burn the chip.
	 */
	mutex_lock(&pdata->lock);

	/* call regulator regmap helper */
	regulator_enable_regmap(rdev);

	mutex_unlock(&pdata->lock);
	return 0;
}