#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cg_item; } ;
struct se_hba {TYPE_1__ hba_group; } ;
struct TYPE_4__ {int /*<<< orphan*/  cg_item; } ;
struct se_device {char* dev_alias; TYPE_2__ dev_group; int /*<<< orphan*/  dev_flags; struct se_hba* se_hba; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DF_USING_ALIAS ; 
 int EINVAL ; 
 int SE_DEV_ALIAS_LEN ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_alias_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_device *dev = to_device(item);
	struct se_hba *hba = dev->se_hba;
	ssize_t read_bytes;

	if (count > (SE_DEV_ALIAS_LEN-1)) {
		pr_err("alias count: %d exceeds"
			" SE_DEV_ALIAS_LEN-1: %u\n", (int)count,
			SE_DEV_ALIAS_LEN-1);
		return -EINVAL;
	}

	read_bytes = snprintf(&dev->dev_alias[0], SE_DEV_ALIAS_LEN, "%s", page);
	if (!read_bytes)
		return -EINVAL;
	if (dev->dev_alias[read_bytes - 1] == '\n')
		dev->dev_alias[read_bytes - 1] = '\0';

	dev->dev_flags |= DF_USING_ALIAS;

	pr_debug("Target_Core_ConfigFS: %s/%s set alias: %s\n",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		dev->dev_alias);

	return read_bytes;
}