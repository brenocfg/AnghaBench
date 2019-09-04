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
typedef  int /*<<< orphan*/  u64 ;
struct scrub_ctx {int readonly; int /*<<< orphan*/  stat; int /*<<< orphan*/  workers_pending; int /*<<< orphan*/  list_wait; int /*<<< orphan*/  bios_in_flight; } ;
struct btrfs_scrub_progress {int dummy; } ;
struct btrfs_fs_info {int nodesize; int sectorsize; int /*<<< orphan*/  scrub_lock; int /*<<< orphan*/  scrub_pause_wait; int /*<<< orphan*/  scrubs_running; TYPE_1__* fs_devices; int /*<<< orphan*/  dev_replace; } ;
struct btrfs_device {struct scrub_ctx* scrub_ctx; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STATE_IN_FS_METADATA ; 
 int /*<<< orphan*/  BTRFS_DEV_STATE_MISSING ; 
 int /*<<< orphan*/  BTRFS_DEV_STATE_REPLACE_TGT ; 
 int /*<<< orphan*/  BTRFS_DEV_STATE_WRITEABLE ; 
 int BTRFS_STRIPE_LEN ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct scrub_ctx*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct scrub_ctx*) ; 
 int SCRUB_MAX_PAGES_PER_BLOCK ; 
 int /*<<< orphan*/  __scrub_blocked_if_needed (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_dev_replace_is_ongoing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_dev_replace_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_dev_replace_read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int,int,...) ; 
 int /*<<< orphan*/  btrfs_err_in_rcu (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_err_rl (struct btrfs_fs_info*,char*,int,int) ; 
 struct btrfs_device* btrfs_find_device (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_fs_closing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_scrub_progress*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_str_deref (int /*<<< orphan*/ ) ; 
 int scrub_enumerate_chunks (struct scrub_ctx*,struct btrfs_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scrub_put_ctx (struct scrub_ctx*) ; 
 struct scrub_ctx* scrub_setup_ctx (struct btrfs_device*,int) ; 
 int scrub_supers (struct scrub_ctx*,struct btrfs_device*) ; 
 int scrub_workers_get (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  scrub_workers_put (struct btrfs_fs_info*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int btrfs_scrub_dev(struct btrfs_fs_info *fs_info, u64 devid, u64 start,
		    u64 end, struct btrfs_scrub_progress *progress,
		    int readonly, int is_dev_replace)
{
	struct scrub_ctx *sctx;
	int ret;
	struct btrfs_device *dev;

	if (btrfs_fs_closing(fs_info))
		return -EINVAL;

	if (fs_info->nodesize > BTRFS_STRIPE_LEN) {
		/*
		 * in this case scrub is unable to calculate the checksum
		 * the way scrub is implemented. Do not handle this
		 * situation at all because it won't ever happen.
		 */
		btrfs_err(fs_info,
			   "scrub: size assumption nodesize <= BTRFS_STRIPE_LEN (%d <= %d) fails",
		       fs_info->nodesize,
		       BTRFS_STRIPE_LEN);
		return -EINVAL;
	}

	if (fs_info->sectorsize != PAGE_SIZE) {
		/* not supported for data w/o checksums */
		btrfs_err_rl(fs_info,
			   "scrub: size assumption sectorsize != PAGE_SIZE (%d != %lu) fails",
		       fs_info->sectorsize, PAGE_SIZE);
		return -EINVAL;
	}

	if (fs_info->nodesize >
	    PAGE_SIZE * SCRUB_MAX_PAGES_PER_BLOCK ||
	    fs_info->sectorsize > PAGE_SIZE * SCRUB_MAX_PAGES_PER_BLOCK) {
		/*
		 * would exhaust the array bounds of pagev member in
		 * struct scrub_block
		 */
		btrfs_err(fs_info,
			  "scrub: size assumption nodesize and sectorsize <= SCRUB_MAX_PAGES_PER_BLOCK (%d <= %d && %d <= %d) fails",
		       fs_info->nodesize,
		       SCRUB_MAX_PAGES_PER_BLOCK,
		       fs_info->sectorsize,
		       SCRUB_MAX_PAGES_PER_BLOCK);
		return -EINVAL;
	}


	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	dev = btrfs_find_device(fs_info, devid, NULL, NULL);
	if (!dev || (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state) &&
		     !is_dev_replace)) {
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		return -ENODEV;
	}

	if (!is_dev_replace && !readonly &&
	    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state)) {
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		btrfs_err_in_rcu(fs_info, "scrub: device %s is not writable",
				rcu_str_deref(dev->name));
		return -EROFS;
	}

	mutex_lock(&fs_info->scrub_lock);
	if (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
	    test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &dev->dev_state)) {
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		return -EIO;
	}

	btrfs_dev_replace_read_lock(&fs_info->dev_replace);
	if (dev->scrub_ctx ||
	    (!is_dev_replace &&
	     btrfs_dev_replace_is_ongoing(&fs_info->dev_replace))) {
		btrfs_dev_replace_read_unlock(&fs_info->dev_replace);
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		return -EINPROGRESS;
	}
	btrfs_dev_replace_read_unlock(&fs_info->dev_replace);

	ret = scrub_workers_get(fs_info, is_dev_replace);
	if (ret) {
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		return ret;
	}

	sctx = scrub_setup_ctx(dev, is_dev_replace);
	if (IS_ERR(sctx)) {
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		scrub_workers_put(fs_info);
		return PTR_ERR(sctx);
	}
	sctx->readonly = readonly;
	dev->scrub_ctx = sctx;
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	/*
	 * checking @scrub_pause_req here, we can avoid
	 * race between committing transaction and scrubbing.
	 */
	__scrub_blocked_if_needed(fs_info);
	atomic_inc(&fs_info->scrubs_running);
	mutex_unlock(&fs_info->scrub_lock);

	if (!is_dev_replace) {
		/*
		 * by holding device list mutex, we can
		 * kick off writing super in log tree sync.
		 */
		mutex_lock(&fs_info->fs_devices->device_list_mutex);
		ret = scrub_supers(sctx, dev);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
	}

	if (!ret)
		ret = scrub_enumerate_chunks(sctx, dev, start, end,
					     is_dev_replace);

	wait_event(sctx->list_wait, atomic_read(&sctx->bios_in_flight) == 0);
	atomic_dec(&fs_info->scrubs_running);
	wake_up(&fs_info->scrub_pause_wait);

	wait_event(sctx->list_wait, atomic_read(&sctx->workers_pending) == 0);

	if (progress)
		memcpy(progress, &sctx->stat, sizeof(*progress));

	mutex_lock(&fs_info->scrub_lock);
	dev->scrub_ctx = NULL;
	scrub_workers_put(fs_info);
	mutex_unlock(&fs_info->scrub_lock);

	scrub_put_ctx(sctx);

	return ret;
}