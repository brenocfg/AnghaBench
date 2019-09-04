#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_dev_attrib {int emulate_tas; TYPE_1__* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ export_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,TYPE_1__*,scalar_t__) ; 
 int strtobool (char const*,int*) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t emulate_tas_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	if (da->da_dev->export_count) {
		pr_err("dev[%p]: Unable to change SE Device TAS while"
			" export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		return -EINVAL;
	}
	da->emulate_tas = flag;
	pr_debug("dev[%p]: SE Device TASK_ABORTED status bit: %s\n",
		da->da_dev, flag ? "Enabled" : "Disabled");

	return count;
}