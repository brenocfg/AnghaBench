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
struct rsi_hw {struct rsi_debugfs* dfsentry; } ;
struct rsi_debugfs {int /*<<< orphan*/  subdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 

void rsi_remove_dbgfs(struct rsi_hw *adapter)
{
	struct rsi_debugfs *dev_dbgfs = adapter->dfsentry;

	if (!dev_dbgfs)
		return;

	debugfs_remove_recursive(dev_dbgfs->subdir);
}