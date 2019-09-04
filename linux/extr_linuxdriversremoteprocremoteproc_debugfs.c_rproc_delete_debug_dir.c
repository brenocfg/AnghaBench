#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rproc {int /*<<< orphan*/  dbg_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 

void rproc_delete_debug_dir(struct rproc *rproc)
{
	if (!rproc->dbg_dir)
		return;

	debugfs_remove_recursive(rproc->dbg_dir);
}