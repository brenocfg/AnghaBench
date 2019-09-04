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
struct controller {TYPE_1__* pci_dev; int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debug_ops ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct controller*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root ; 

void cpqhp_create_debugfs_files(struct controller *ctrl)
{
	ctrl->dentry = debugfs_create_file(dev_name(&ctrl->pci_dev->dev),
					   S_IRUGO, root, ctrl, &debug_ops);
}