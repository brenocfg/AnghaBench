#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct reada_zone {scalar_t__ elems; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; struct btrfs_device* device; } ;
struct btrfs_key {int dummy; } ;
struct reada_extent {int refcnt; int nzones; struct reada_zone** zones; int /*<<< orphan*/  lock; int /*<<< orphan*/  extctl; struct btrfs_key top; scalar_t__ logical; } ;
struct TYPE_4__ {int /*<<< orphan*/  rwsem; struct btrfs_device* tgtdev; } ;
struct btrfs_fs_info {scalar_t__ nodesize; int /*<<< orphan*/  reada_lock; TYPE_2__ dev_replace; int /*<<< orphan*/  reada_tree; } ;
struct btrfs_device {int /*<<< orphan*/  reada_extents; int /*<<< orphan*/  bdev; } ;
struct btrfs_bio {scalar_t__ num_stripes; int num_tgtdevs; TYPE_1__* stripes; } ;
struct TYPE_3__ {struct btrfs_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_MAP_GET_READ_MIRRORS ; 
 scalar_t__ BTRFS_MAX_MIRRORS ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SHIFT ; 
 int btrfs_dev_replace_is_ongoing (TYPE_2__*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__) ; 
 int btrfs_map_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,struct btrfs_bio**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_bbio (struct btrfs_bio*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct reada_extent*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct reada_extent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct reada_extent*) ; 
 struct reada_extent* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 struct reada_zone* reada_find_zone (struct btrfs_device*,scalar_t__,struct btrfs_bio*) ; 
 int /*<<< orphan*/  reada_zone_release ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct reada_extent *reada_find_extent(struct btrfs_fs_info *fs_info,
					      u64 logical,
					      struct btrfs_key *top)
{
	int ret;
	struct reada_extent *re = NULL;
	struct reada_extent *re_exist = NULL;
	struct btrfs_bio *bbio = NULL;
	struct btrfs_device *dev;
	struct btrfs_device *prev_dev;
	u64 length;
	int real_stripes;
	int nzones = 0;
	unsigned long index = logical >> PAGE_SHIFT;
	int dev_replace_is_ongoing;
	int have_zone = 0;

	spin_lock(&fs_info->reada_lock);
	re = radix_tree_lookup(&fs_info->reada_tree, index);
	if (re)
		re->refcnt++;
	spin_unlock(&fs_info->reada_lock);

	if (re)
		return re;

	re = kzalloc(sizeof(*re), GFP_KERNEL);
	if (!re)
		return NULL;

	re->logical = logical;
	re->top = *top;
	INIT_LIST_HEAD(&re->extctl);
	spin_lock_init(&re->lock);
	re->refcnt = 1;

	/*
	 * map block
	 */
	length = fs_info->nodesize;
	ret = btrfs_map_block(fs_info, BTRFS_MAP_GET_READ_MIRRORS, logical,
			&length, &bbio, 0);
	if (ret || !bbio || length < fs_info->nodesize)
		goto error;

	if (bbio->num_stripes > BTRFS_MAX_MIRRORS) {
		btrfs_err(fs_info,
			   "readahead: more than %d copies not supported",
			   BTRFS_MAX_MIRRORS);
		goto error;
	}

	real_stripes = bbio->num_stripes - bbio->num_tgtdevs;
	for (nzones = 0; nzones < real_stripes; ++nzones) {
		struct reada_zone *zone;

		dev = bbio->stripes[nzones].dev;

		/* cannot read ahead on missing device. */
		if (!dev->bdev)
			continue;

		zone = reada_find_zone(dev, logical, bbio);
		if (!zone)
			continue;

		re->zones[re->nzones++] = zone;
		spin_lock(&zone->lock);
		if (!zone->elems)
			kref_get(&zone->refcnt);
		++zone->elems;
		spin_unlock(&zone->lock);
		spin_lock(&fs_info->reada_lock);
		kref_put(&zone->refcnt, reada_zone_release);
		spin_unlock(&fs_info->reada_lock);
	}
	if (re->nzones == 0) {
		/* not a single zone found, error and out */
		goto error;
	}

	/* Insert extent in reada tree + all per-device trees, all or nothing */
	down_read(&fs_info->dev_replace.rwsem);
	ret = radix_tree_preload(GFP_KERNEL);
	if (ret) {
		up_read(&fs_info->dev_replace.rwsem);
		goto error;
	}

	spin_lock(&fs_info->reada_lock);
	ret = radix_tree_insert(&fs_info->reada_tree, index, re);
	if (ret == -EEXIST) {
		re_exist = radix_tree_lookup(&fs_info->reada_tree, index);
		re_exist->refcnt++;
		spin_unlock(&fs_info->reada_lock);
		radix_tree_preload_end();
		up_read(&fs_info->dev_replace.rwsem);
		goto error;
	}
	if (ret) {
		spin_unlock(&fs_info->reada_lock);
		radix_tree_preload_end();
		up_read(&fs_info->dev_replace.rwsem);
		goto error;
	}
	radix_tree_preload_end();
	prev_dev = NULL;
	dev_replace_is_ongoing = btrfs_dev_replace_is_ongoing(
			&fs_info->dev_replace);
	for (nzones = 0; nzones < re->nzones; ++nzones) {
		dev = re->zones[nzones]->device;

		if (dev == prev_dev) {
			/*
			 * in case of DUP, just add the first zone. As both
			 * are on the same device, there's nothing to gain
			 * from adding both.
			 * Also, it wouldn't work, as the tree is per device
			 * and adding would fail with EEXIST
			 */
			continue;
		}
		if (!dev->bdev)
			continue;

		if (dev_replace_is_ongoing &&
		    dev == fs_info->dev_replace.tgtdev) {
			/*
			 * as this device is selected for reading only as
			 * a last resort, skip it for read ahead.
			 */
			continue;
		}
		prev_dev = dev;
		ret = radix_tree_insert(&dev->reada_extents, index, re);
		if (ret) {
			while (--nzones >= 0) {
				dev = re->zones[nzones]->device;
				BUG_ON(dev == NULL);
				/* ignore whether the entry was inserted */
				radix_tree_delete(&dev->reada_extents, index);
			}
			radix_tree_delete(&fs_info->reada_tree, index);
			spin_unlock(&fs_info->reada_lock);
			up_read(&fs_info->dev_replace.rwsem);
			goto error;
		}
		have_zone = 1;
	}
	spin_unlock(&fs_info->reada_lock);
	up_read(&fs_info->dev_replace.rwsem);

	if (!have_zone)
		goto error;

	btrfs_put_bbio(bbio);
	return re;

error:
	for (nzones = 0; nzones < re->nzones; ++nzones) {
		struct reada_zone *zone;

		zone = re->zones[nzones];
		kref_get(&zone->refcnt);
		spin_lock(&zone->lock);
		--zone->elems;
		if (zone->elems == 0) {
			/*
			 * no fs_info->reada_lock needed, as this can't be
			 * the last ref
			 */
			kref_put(&zone->refcnt, reada_zone_release);
		}
		spin_unlock(&zone->lock);

		spin_lock(&fs_info->reada_lock);
		kref_put(&zone->refcnt, reada_zone_release);
		spin_unlock(&fs_info->reada_lock);
	}
	btrfs_put_bbio(bbio);
	kfree(re);
	return re_exist;
}