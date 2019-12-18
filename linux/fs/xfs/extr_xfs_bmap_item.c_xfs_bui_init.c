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
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {uintptr_t bui_id; int /*<<< orphan*/  bui_nextents; } ;
struct xfs_bui_log_item {int /*<<< orphan*/  bui_refcount; int /*<<< orphan*/  bui_next_extent; TYPE_1__ bui_format; int /*<<< orphan*/  bui_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  XFS_LI_BUI ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct xfs_bui_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bui_item_ops ; 
 int /*<<< orphan*/  xfs_bui_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct xfs_bui_log_item *
xfs_bui_init(
	struct xfs_mount		*mp)

{
	struct xfs_bui_log_item		*buip;

	buip = kmem_zone_zalloc(xfs_bui_zone, 0);

	xfs_log_item_init(mp, &buip->bui_item, XFS_LI_BUI, &xfs_bui_item_ops);
	buip->bui_format.bui_nextents = XFS_BUI_MAX_FAST_EXTENTS;
	buip->bui_format.bui_id = (uintptr_t)(void *)buip;
	atomic_set(&buip->bui_next_extent, 0);
	atomic_set(&buip->bui_refcount, 2);

	return buip;
}