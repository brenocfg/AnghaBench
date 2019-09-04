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
struct TYPE_2__ {scalar_t__ cui_nextents; } ;
struct xfs_cui_log_item {TYPE_1__ cui_format; } ;

/* Variables and functions */
 scalar_t__ XFS_CUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  kmem_free (struct xfs_cui_log_item*) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_cui_log_item*) ; 
 int /*<<< orphan*/  xfs_cui_zone ; 

void
xfs_cui_item_free(
	struct xfs_cui_log_item	*cuip)
{
	if (cuip->cui_format.cui_nextents > XFS_CUI_MAX_FAST_EXTENTS)
		kmem_free(cuip);
	else
		kmem_zone_free(xfs_cui_zone, cuip);
}