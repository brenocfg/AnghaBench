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
struct btrfs_fs_info {int dummy; } ;
struct __btrfs_workqueue {int limit_active; int current_active; int thresh; int /*<<< orphan*/  thres_lock; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  ordered_list; void* normal_wq; int /*<<< orphan*/  pending; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int DFT_THRESHOLD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NO_THRESHOLD ; 
 unsigned int WQ_HIGHPRI ; 
 void* alloc_workqueue (char*,unsigned int,int,char const*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct __btrfs_workqueue*) ; 
 struct __btrfs_workqueue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_workqueue_alloc (struct __btrfs_workqueue*,char const*,unsigned int) ; 

__attribute__((used)) static struct __btrfs_workqueue *
__btrfs_alloc_workqueue(struct btrfs_fs_info *fs_info, const char *name,
			unsigned int flags, int limit_active, int thresh)
{
	struct __btrfs_workqueue *ret = kzalloc(sizeof(*ret), GFP_KERNEL);

	if (!ret)
		return NULL;

	ret->fs_info = fs_info;
	ret->limit_active = limit_active;
	atomic_set(&ret->pending, 0);
	if (thresh == 0)
		thresh = DFT_THRESHOLD;
	/* For low threshold, disabling threshold is a better choice */
	if (thresh < DFT_THRESHOLD) {
		ret->current_active = limit_active;
		ret->thresh = NO_THRESHOLD;
	} else {
		/*
		 * For threshold-able wq, let its concurrency grow on demand.
		 * Use minimal max_active at alloc time to reduce resource
		 * usage.
		 */
		ret->current_active = 1;
		ret->thresh = thresh;
	}

	if (flags & WQ_HIGHPRI)
		ret->normal_wq = alloc_workqueue("btrfs-%s-high", flags,
						 ret->current_active, name);
	else
		ret->normal_wq = alloc_workqueue("btrfs-%s", flags,
						 ret->current_active, name);
	if (!ret->normal_wq) {
		kfree(ret);
		return NULL;
	}

	INIT_LIST_HEAD(&ret->ordered_list);
	spin_lock_init(&ret->list_lock);
	spin_lock_init(&ret->thres_lock);
	trace_btrfs_workqueue_alloc(ret, name, flags & WQ_HIGHPRI);
	return ret;
}