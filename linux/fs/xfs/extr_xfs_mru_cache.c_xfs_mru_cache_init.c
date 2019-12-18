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

/* Variables and functions */
 int ENOMEM ; 
 int WQ_FREEZABLE ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int) ; 
 int /*<<< orphan*/  xfs_mru_reap_wq ; 

int
xfs_mru_cache_init(void)
{
	xfs_mru_reap_wq = alloc_workqueue("xfs_mru_cache",
				WQ_MEM_RECLAIM|WQ_FREEZABLE, 1);
	if (!xfs_mru_reap_wq)
		return -ENOMEM;
	return 0;
}