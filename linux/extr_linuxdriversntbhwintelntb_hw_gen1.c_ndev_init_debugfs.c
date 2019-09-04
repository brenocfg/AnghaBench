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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct intel_ntb_dev {int /*<<< orphan*/ * debugfs_dir; int /*<<< orphan*/ * debugfs_info; TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct intel_ntb_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_dir ; 
 int /*<<< orphan*/  intel_ntb_debugfs_info ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ndev_init_debugfs(struct intel_ntb_dev *ndev)
{
	if (!debugfs_dir) {
		ndev->debugfs_dir = NULL;
		ndev->debugfs_info = NULL;
	} else {
		ndev->debugfs_dir =
			debugfs_create_dir(pci_name(ndev->ntb.pdev),
					   debugfs_dir);
		if (!ndev->debugfs_dir)
			ndev->debugfs_info = NULL;
		else
			ndev->debugfs_info =
				debugfs_create_file("info", S_IRUSR,
						    ndev->debugfs_dir, ndev,
						    &intel_ntb_debugfs_info);
	}
}