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
 int ENOMEM ; 
 int _opp_add_v1 (struct opp_table*,struct device*,unsigned long,unsigned long,int) ; 
 struct opp_table* dev_pm_opp_get_opp_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 

int dev_pm_opp_add(struct device *dev, unsigned long freq, unsigned long u_volt)
{
	struct opp_table *opp_table;
	int ret;

	opp_table = dev_pm_opp_get_opp_table(dev);
	if (!opp_table)
		return -ENOMEM;

	ret = _opp_add_v1(opp_table, dev, freq, u_volt, true);

	dev_pm_opp_put_opp_table(opp_table);
	return ret;
}