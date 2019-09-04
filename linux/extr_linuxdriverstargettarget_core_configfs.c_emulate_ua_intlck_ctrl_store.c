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
typedef  int u32 ;
struct se_dev_attrib {int emulate_ua_intlck_ctrl; TYPE_1__* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ export_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t emulate_ua_intlck_ctrl_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	u32 val;
	int ret;

	ret = kstrtou32(page, 0, &val);
	if (ret < 0)
		return ret;

	if (val != 0 && val != 1 && val != 2) {
		pr_err("Illegal value %d\n", val);
		return -EINVAL;
	}

	if (da->da_dev->export_count) {
		pr_err("dev[%p]: Unable to change SE Device"
			" UA_INTRLCK_CTRL while export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		return -EINVAL;
	}
	da->emulate_ua_intlck_ctrl = val;
	pr_debug("dev[%p]: SE Device UA_INTRLCK_CTRL flag: %d\n",
		da->da_dev, val);
	return count;
}