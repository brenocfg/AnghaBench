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
struct TYPE_2__ {uintptr_t rui_id; scalar_t__ rui_nextents; } ;
struct xfs_rui_log_item {int /*<<< orphan*/  rui_refcount; int /*<<< orphan*/  rui_next_extent; TYPE_1__ rui_format; int /*<<< orphan*/  rui_item; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_LI_RUI ; 
 scalar_t__ XFS_RUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct xfs_rui_log_item* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_rui_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_item_init (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rui_item_ops ; 
 int /*<<< orphan*/  xfs_rui_log_item_sizeof (scalar_t__) ; 
 int /*<<< orphan*/  xfs_rui_zone ; 

struct xfs_rui_log_item *
xfs_rui_init(
	struct xfs_mount		*mp,
	uint				nextents)

{
	struct xfs_rui_log_item		*ruip;

	ASSERT(nextents > 0);
	if (nextents > XFS_RUI_MAX_FAST_EXTENTS)
		ruip = kmem_zalloc(xfs_rui_log_item_sizeof(nextents), 0);
	else
		ruip = kmem_zone_zalloc(xfs_rui_zone, 0);

	xfs_log_item_init(mp, &ruip->rui_item, XFS_LI_RUI, &xfs_rui_item_ops);
	ruip->rui_format.rui_nextents = nextents;
	ruip->rui_format.rui_id = (uintptr_t)(void *)ruip;
	atomic_set(&ruip->rui_next_extent, 0);
	atomic_set(&ruip->rui_refcount, 2);

	return ruip;
}