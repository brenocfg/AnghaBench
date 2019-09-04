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
struct perf_ctx {int /*<<< orphan*/  dbgfs_dir; TYPE_1__* ntb; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_order ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct perf_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  perf_dbgfs_info ; 
 int /*<<< orphan*/  perf_dbgfs_run ; 
 int /*<<< orphan*/  perf_dbgfs_tcnt ; 
 int /*<<< orphan*/  perf_dbgfs_topdir ; 
 int /*<<< orphan*/  total_order ; 
 int /*<<< orphan*/  use_dma ; 

__attribute__((used)) static void perf_setup_dbgfs(struct perf_ctx *perf)
{
	struct pci_dev *pdev = perf->ntb->pdev;

	perf->dbgfs_dir = debugfs_create_dir(pci_name(pdev), perf_dbgfs_topdir);
	if (!perf->dbgfs_dir) {
		dev_warn(&perf->ntb->dev, "DebugFS unsupported\n");
		return;
	}

	debugfs_create_file("info", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_info);

	debugfs_create_file("run", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_run);

	debugfs_create_file("threads_count", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_tcnt);

	/* They are made read-only for test exec safety and integrity */
	debugfs_create_u8("chunk_order", 0500, perf->dbgfs_dir, &chunk_order);

	debugfs_create_u8("total_order", 0500, perf->dbgfs_dir, &total_order);

	debugfs_create_bool("use_dma", 0500, perf->dbgfs_dir, &use_dma);
}