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
struct thermal_cooling_device {struct devfreq_cooling_device* devdata; } ;
struct device {int dummy; } ;
struct devfreq_cooling_device {unsigned long cooling_state; unsigned long freq_table_size; struct devfreq* devfreq; } ;
struct TYPE_2__ {struct device* parent; } ;
struct devfreq {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long) ; 
 int partition_enable_opps (struct devfreq_cooling_device*,unsigned long) ; 

__attribute__((used)) static int devfreq_cooling_set_cur_state(struct thermal_cooling_device *cdev,
					 unsigned long state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq *df = dfc->devfreq;
	struct device *dev = df->dev.parent;
	int ret;

	if (state == dfc->cooling_state)
		return 0;

	dev_dbg(dev, "Setting cooling state %lu\n", state);

	if (state >= dfc->freq_table_size)
		return -EINVAL;

	ret = partition_enable_opps(dfc, state);
	if (ret)
		return ret;

	dfc->cooling_state = state;

	return 0;
}