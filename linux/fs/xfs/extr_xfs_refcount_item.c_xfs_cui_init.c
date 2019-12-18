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
typedef  scalar_t__ uint ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {uintptr_t cui_id; scalar_t__ cui_nextents; } ;
struct xfs_cui_log_item {int /*<<< orphan*/  cui_refcount; int /*<<< orphan*/  cui_next_extent; TYPE_1__ cui_format; int /*<<< orphan*/  cui_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_CUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  XFS_LI_CUI ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct xfs_cui_log_item* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_cui_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_cui_item_ops ; 
 int /*<<< orphan*/  xfs_cui_log_item_sizeof (scalar_t__) ; 
 int /*<<< orphan*/  xfs_cui_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct xfs_cui_log_item *
xfs_cui_init(
	struct xfs_mount		*mp,
	uint				nextents)

{
	struct xfs_cui_log_item		*cuip;

	ASSERT(nextents > 0);
	if (nextents > XFS_CUI_MAX_FAST_EXTENTS)
		cuip = kmem_zalloc(xfs_cui_log_item_sizeof(nextents),
				0);
	else
		cuip = kmem_zone_zalloc(xfs_cui_zone, 0);

	xfs_log_item_init(mp, &cuip->cui_item, XFS_LI_CUI, &xfs_cui_item_ops);
	cuip->cui_format.cui_nextents = nextents;
	cuip->cui_format.cui_id = (uintptr_t)(void *)cuip;
	atomic_set(&cuip->cui_next_extent, 0);
	atomic_set(&cuip->cui_refcount, 2);

	return cuip;
}