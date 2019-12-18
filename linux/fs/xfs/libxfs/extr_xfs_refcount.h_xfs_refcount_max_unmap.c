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
typedef  int xfs_fileoff_t ;

/* Variables and functions */
 int XFS_REFCOUNT_ITEM_OVERHEAD ; 

__attribute__((used)) static inline xfs_fileoff_t xfs_refcount_max_unmap(int log_res)
{
	return (log_res * 3 / 4) / XFS_REFCOUNT_ITEM_OVERHEAD;
}