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
struct se_device {int /*<<< orphan*/  delayed_cmd_lock; int /*<<< orphan*/  delayed_cmd_list; int /*<<< orphan*/  dev_ordered_sync; int /*<<< orphan*/  simple_cmds; TYPE_1__* transport; } ;
struct se_cmd {int sam_task_attr; int /*<<< orphan*/ * t_task_cdb; int /*<<< orphan*/  se_delayed_node; int /*<<< orphan*/  se_cmd_flags; struct se_device* se_dev; } ;
struct TYPE_2__ {int transport_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCF_TASK_ATTR_SET ; 
#define  TCM_HEAD_TAG 129 
#define  TCM_ORDERED_TAG 128 
 int TRANSPORT_FLAG_PASSTHROUGH ; 
 int /*<<< orphan*/  atomic_inc_mb (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool target_handle_task_attr(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;

	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		return false;

	cmd->se_cmd_flags |= SCF_TASK_ATTR_SET;

	/*
	 * Check for the existence of HEAD_OF_QUEUE, and if true return 1
	 * to allow the passed struct se_cmd list of tasks to the front of the list.
	 */
	switch (cmd->sam_task_attr) {
	case TCM_HEAD_TAG:
		pr_debug("Added HEAD_OF_QUEUE for CDB: 0x%02x\n",
			 cmd->t_task_cdb[0]);
		return false;
	case TCM_ORDERED_TAG:
		atomic_inc_mb(&dev->dev_ordered_sync);

		pr_debug("Added ORDERED for CDB: 0x%02x to ordered list\n",
			 cmd->t_task_cdb[0]);

		/*
		 * Execute an ORDERED command if no other older commands
		 * exist that need to be completed first.
		 */
		if (!atomic_read(&dev->simple_cmds))
			return false;
		break;
	default:
		/*
		 * For SIMPLE and UNTAGGED Task Attribute commands
		 */
		atomic_inc_mb(&dev->simple_cmds);
		break;
	}

	if (atomic_read(&dev->dev_ordered_sync) == 0)
		return false;

	spin_lock(&dev->delayed_cmd_lock);
	list_add_tail(&cmd->se_delayed_node, &dev->delayed_cmd_list);
	spin_unlock(&dev->delayed_cmd_lock);

	pr_debug("Added CDB: 0x%02x Task Attr: 0x%02x to delayed CMD listn",
		cmd->t_task_cdb[0], cmd->sam_task_attr);
	return true;
}