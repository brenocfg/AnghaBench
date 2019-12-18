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
typedef  int u32 ;
struct btrfs_fs_info {int thread_pool_size; void* qgroup_rescan_workers; void* delayed_workers; void* fixup_workers; void* readahead_workers; void* caching_workers; void* rmw_workers; void* endio_freespace_worker; void* endio_raid56_workers; void* endio_write_workers; void* endio_repair_workers; void* endio_meta_write_workers; void* endio_meta_workers; void* endio_workers; void* flush_workers; void* submit_workers; void* delalloc_workers; void* workers; } ;
struct btrfs_fs_devices {int /*<<< orphan*/  num_devices; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int WQ_FREEZABLE ; 
 unsigned int WQ_HIGHPRI ; 
 unsigned int WQ_MEM_RECLAIM ; 
 unsigned int WQ_UNBOUND ; 
 void* btrfs_alloc_workqueue (struct btrfs_fs_info*,char*,unsigned int,int,int) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static int btrfs_init_workqueues(struct btrfs_fs_info *fs_info,
		struct btrfs_fs_devices *fs_devices)
{
	u32 max_active = fs_info->thread_pool_size;
	unsigned int flags = WQ_MEM_RECLAIM | WQ_FREEZABLE | WQ_UNBOUND;

	fs_info->workers =
		btrfs_alloc_workqueue(fs_info, "worker",
				      flags | WQ_HIGHPRI, max_active, 16);

	fs_info->delalloc_workers =
		btrfs_alloc_workqueue(fs_info, "delalloc",
				      flags, max_active, 2);

	fs_info->flush_workers =
		btrfs_alloc_workqueue(fs_info, "flush_delalloc",
				      flags, max_active, 0);

	fs_info->caching_workers =
		btrfs_alloc_workqueue(fs_info, "cache", flags, max_active, 0);

	/*
	 * a higher idle thresh on the submit workers makes it much more
	 * likely that bios will be send down in a sane order to the
	 * devices
	 */
	fs_info->submit_workers =
		btrfs_alloc_workqueue(fs_info, "submit", flags,
				      min_t(u64, fs_devices->num_devices,
					    max_active), 64);

	fs_info->fixup_workers =
		btrfs_alloc_workqueue(fs_info, "fixup", flags, 1, 0);

	/*
	 * endios are largely parallel and should have a very
	 * low idle thresh
	 */
	fs_info->endio_workers =
		btrfs_alloc_workqueue(fs_info, "endio", flags, max_active, 4);
	fs_info->endio_meta_workers =
		btrfs_alloc_workqueue(fs_info, "endio-meta", flags,
				      max_active, 4);
	fs_info->endio_meta_write_workers =
		btrfs_alloc_workqueue(fs_info, "endio-meta-write", flags,
				      max_active, 2);
	fs_info->endio_raid56_workers =
		btrfs_alloc_workqueue(fs_info, "endio-raid56", flags,
				      max_active, 4);
	fs_info->endio_repair_workers =
		btrfs_alloc_workqueue(fs_info, "endio-repair", flags, 1, 0);
	fs_info->rmw_workers =
		btrfs_alloc_workqueue(fs_info, "rmw", flags, max_active, 2);
	fs_info->endio_write_workers =
		btrfs_alloc_workqueue(fs_info, "endio-write", flags,
				      max_active, 2);
	fs_info->endio_freespace_worker =
		btrfs_alloc_workqueue(fs_info, "freespace-write", flags,
				      max_active, 0);
	fs_info->delayed_workers =
		btrfs_alloc_workqueue(fs_info, "delayed-meta", flags,
				      max_active, 0);
	fs_info->readahead_workers =
		btrfs_alloc_workqueue(fs_info, "readahead", flags,
				      max_active, 2);
	fs_info->qgroup_rescan_workers =
		btrfs_alloc_workqueue(fs_info, "qgroup-rescan", flags, 1, 0);

	if (!(fs_info->workers && fs_info->delalloc_workers &&
	      fs_info->submit_workers && fs_info->flush_workers &&
	      fs_info->endio_workers && fs_info->endio_meta_workers &&
	      fs_info->endio_meta_write_workers &&
	      fs_info->endio_repair_workers &&
	      fs_info->endio_write_workers && fs_info->endio_raid56_workers &&
	      fs_info->endio_freespace_worker && fs_info->rmw_workers &&
	      fs_info->caching_workers && fs_info->readahead_workers &&
	      fs_info->fixup_workers && fs_info->delayed_workers &&
	      fs_info->qgroup_rescan_workers)) {
		return -ENOMEM;
	}

	return 0;
}