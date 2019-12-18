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
struct omap_mcbsp_st_data {int nr_taps; int /*<<< orphan*/ * taps; } ;
struct omap_mcbsp {int /*<<< orphan*/  lock; struct omap_mcbsp_st_data* st_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct omap_mcbsp* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t st_taps_show(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	struct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	ssize_t status = 0;
	int i;

	spin_lock_irq(&mcbsp->lock);
	for (i = 0; i < st_data->nr_taps; i++)
		status += sprintf(&buf[status], (i ? ", %d" : "%d"),
				  st_data->taps[i]);
	if (i)
		status += sprintf(&buf[status], "\n");
	spin_unlock_irq(&mcbsp->lock);

	return status;
}