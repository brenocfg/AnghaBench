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
struct TYPE_2__ {scalar_t__ rui_nextents; } ;
struct xfs_rui_log_item {TYPE_1__ rui_format; } ;

/* Variables and functions */
 scalar_t__ XFS_RUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  kmem_free (struct xfs_rui_log_item*) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_rui_log_item*) ; 
 int /*<<< orphan*/  xfs_rui_zone ; 

void
xfs_rui_item_free(
	struct xfs_rui_log_item	*ruip)
{
	if (ruip->rui_format.rui_nextents > XFS_RUI_MAX_FAST_EXTENTS)
		kmem_free(ruip);
	else
		kmem_zone_free(xfs_rui_zone, ruip);
}