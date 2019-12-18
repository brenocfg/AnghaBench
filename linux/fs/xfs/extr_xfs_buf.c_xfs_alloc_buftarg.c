#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  seeks; int /*<<< orphan*/  scan_objects; int /*<<< orphan*/  count_objects; } ;
struct TYPE_7__ {int /*<<< orphan*/  bt_lru; int /*<<< orphan*/  bt_io_count; TYPE_4__ bt_shrinker; struct dax_device* bt_daxdev; struct block_device* bt_bdev; int /*<<< orphan*/  bt_dev; struct xfs_mount* bt_mount; } ;
typedef  TYPE_1__ xfs_buftarg_t ;
struct xfs_mount {int dummy; } ;
struct dax_device {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  SHRINKER_NUMA_AWARE ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ list_lru_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_shrinker (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_buftarg_shrink_count ; 
 int /*<<< orphan*/  xfs_buftarg_shrink_scan ; 
 scalar_t__ xfs_setsize_buftarg_early (TYPE_1__*,struct block_device*) ; 

xfs_buftarg_t *
xfs_alloc_buftarg(
	struct xfs_mount	*mp,
	struct block_device	*bdev,
	struct dax_device	*dax_dev)
{
	xfs_buftarg_t		*btp;

	btp = kmem_zalloc(sizeof(*btp), KM_NOFS);

	btp->bt_mount = mp;
	btp->bt_dev =  bdev->bd_dev;
	btp->bt_bdev = bdev;
	btp->bt_daxdev = dax_dev;

	if (xfs_setsize_buftarg_early(btp, bdev))
		goto error_free;

	if (list_lru_init(&btp->bt_lru))
		goto error_free;

	if (percpu_counter_init(&btp->bt_io_count, 0, GFP_KERNEL))
		goto error_lru;

	btp->bt_shrinker.count_objects = xfs_buftarg_shrink_count;
	btp->bt_shrinker.scan_objects = xfs_buftarg_shrink_scan;
	btp->bt_shrinker.seeks = DEFAULT_SEEKS;
	btp->bt_shrinker.flags = SHRINKER_NUMA_AWARE;
	if (register_shrinker(&btp->bt_shrinker))
		goto error_pcpu;
	return btp;

error_pcpu:
	percpu_counter_destroy(&btp->bt_io_count);
error_lru:
	list_lru_destroy(&btp->bt_lru);
error_free:
	kmem_free(btp);
	return NULL;
}