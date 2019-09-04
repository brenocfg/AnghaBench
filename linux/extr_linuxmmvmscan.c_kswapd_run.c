#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * kswapd; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_1__* NODE_DATA (int) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SYSTEM_RUNNING ; 
 int /*<<< orphan*/  kswapd ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ system_state ; 

int kswapd_run(int nid)
{
	pg_data_t *pgdat = NODE_DATA(nid);
	int ret = 0;

	if (pgdat->kswapd)
		return 0;

	pgdat->kswapd = kthread_run(kswapd, pgdat, "kswapd%d", nid);
	if (IS_ERR(pgdat->kswapd)) {
		/* failure at boot is fatal */
		BUG_ON(system_state < SYSTEM_RUNNING);
		pr_err("Failed to start kswapd on node %d\n", nid);
		ret = PTR_ERR(pgdat->kswapd);
		pgdat->kswapd = NULL;
	}
	return ret;
}