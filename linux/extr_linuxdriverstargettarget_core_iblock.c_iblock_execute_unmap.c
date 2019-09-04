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
struct se_device {int dummy; } ;
struct se_cmd {struct se_device* se_dev; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {struct block_device* ibd_bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* IBLOCK_DEV (struct se_device*) ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int blkdev_issue_discard (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  target_to_linux_sector (struct se_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_unmap(struct se_cmd *cmd, sector_t lba, sector_t nolb)
{
	struct block_device *bdev = IBLOCK_DEV(cmd->se_dev)->ibd_bd;
	struct se_device *dev = cmd->se_dev;
	int ret;

	ret = blkdev_issue_discard(bdev,
				   target_to_linux_sector(dev, lba),
				   target_to_linux_sector(dev,  nolb),
				   GFP_KERNEL, 0);
	if (ret < 0) {
		pr_err("blkdev_issue_discard() failed: %d\n", ret);
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	return 0;
}