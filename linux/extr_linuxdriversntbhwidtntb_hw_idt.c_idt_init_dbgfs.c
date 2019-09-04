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
struct TYPE_3__ {TYPE_2__* pdev; } ;
struct idt_ntb_dev {TYPE_1__ ntb; int /*<<< orphan*/  dbgfs_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgfs_topdir ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct idt_ntb_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idt_dbgfs_info_ops ; 
 char* pci_name (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int idt_init_dbgfs(struct idt_ntb_dev *ndev)
{
	char devname[64];

	/* If the top directory is not created then do nothing */
	if (IS_ERR_OR_NULL(dbgfs_topdir)) {
		dev_info(&ndev->ntb.pdev->dev, "Top DebugFS directory absent");
		return PTR_ERR(dbgfs_topdir);
	}

	/* Create the info file node */
	snprintf(devname, 64, "info:%s", pci_name(ndev->ntb.pdev));
	ndev->dbgfs_info = debugfs_create_file(devname, 0400, dbgfs_topdir,
		ndev, &idt_dbgfs_info_ops);
	if (IS_ERR(ndev->dbgfs_info)) {
		dev_dbg(&ndev->ntb.pdev->dev, "Failed to create DebugFS node");
		return PTR_ERR(ndev->dbgfs_info);
	}

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device DebugFS node created");

	return 0;
}