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
struct opp_table {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct opp_table*) ; 
 struct opp_table* _allocate_opp_table (struct device*) ; 
 struct opp_table* _find_opp_table_unlocked (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_table_lock ; 

struct opp_table *dev_pm_opp_get_opp_table(struct device *dev)
{
	struct opp_table *opp_table;

	/* Hold our table modification lock here */
	mutex_lock(&opp_table_lock);

	opp_table = _find_opp_table_unlocked(dev);
	if (!IS_ERR(opp_table))
		goto unlock;

	opp_table = _allocate_opp_table(dev);

unlock:
	mutex_unlock(&opp_table_lock);

	return opp_table;
}