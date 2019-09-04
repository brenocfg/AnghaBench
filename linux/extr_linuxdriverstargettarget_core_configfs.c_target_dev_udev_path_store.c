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
struct se_device {char* udev_path; TYPE_2__ dev_group; int /*<<< orphan*/  dev_flags; struct se_hba* se_hba; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DF_USING_UDEV_PATH ; 
 int EINVAL ; 
 int SE_UDEV_PATH_LEN ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_udev_path_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_device *dev = to_device(item);
	struct se_hba *hba = dev->se_hba;
	ssize_t read_bytes;

	if (count > (SE_UDEV_PATH_LEN-1)) {
		pr_err("udev_path count: %d exceeds"
			" SE_UDEV_PATH_LEN-1: %u\n", (int)count,
			SE_UDEV_PATH_LEN-1);
		return -EINVAL;
	}

	read_bytes = snprintf(&dev->udev_path[0], SE_UDEV_PATH_LEN,
			"%s", page);
	if (!read_bytes)
		return -EINVAL;
	if (dev->udev_path[read_bytes - 1] == '\n')
		dev->udev_path[read_bytes - 1] = '\0';

	dev->dev_flags |= DF_USING_UDEV_PATH;

	pr_debug("Target_Core_ConfigFS: %s/%s set udev_path: %s\n",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		dev->udev_path);

	return read_bytes;
}