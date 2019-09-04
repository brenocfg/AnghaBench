#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  mask; } ;
struct inotify_inode_mark {int wd; TYPE_2__ fsn_mark; } ;
struct inode {int dummy; } ;
struct idr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucounts; int /*<<< orphan*/  idr_lock; struct idr idr; } ;
struct fsnotify_group {TYPE_1__ inotify_data; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fsnotify_add_inode_mark_locked (TYPE_2__*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_init_mark (TYPE_2__*,struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (TYPE_2__*) ; 
 int /*<<< orphan*/  inc_inotify_watches (int /*<<< orphan*/ ) ; 
 int inotify_add_to_idr (struct idr*,int /*<<< orphan*/ *,struct inotify_inode_mark*) ; 
 int /*<<< orphan*/  inotify_arg_to_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_inode_mark_cachep ; 
 int /*<<< orphan*/  inotify_remove_from_idr (struct fsnotify_group*,struct inotify_inode_mark*) ; 
 struct inotify_inode_mark* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int inotify_new_watch(struct fsnotify_group *group,
			     struct inode *inode,
			     u32 arg)
{
	struct inotify_inode_mark *tmp_i_mark;
	__u32 mask;
	int ret;
	struct idr *idr = &group->inotify_data.idr;
	spinlock_t *idr_lock = &group->inotify_data.idr_lock;

	mask = inotify_arg_to_mask(arg);

	tmp_i_mark = kmem_cache_alloc(inotify_inode_mark_cachep, GFP_KERNEL);
	if (unlikely(!tmp_i_mark))
		return -ENOMEM;

	fsnotify_init_mark(&tmp_i_mark->fsn_mark, group);
	tmp_i_mark->fsn_mark.mask = mask;
	tmp_i_mark->wd = -1;

	ret = inotify_add_to_idr(idr, idr_lock, tmp_i_mark);
	if (ret)
		goto out_err;

	/* increment the number of watches the user has */
	if (!inc_inotify_watches(group->inotify_data.ucounts)) {
		inotify_remove_from_idr(group, tmp_i_mark);
		ret = -ENOSPC;
		goto out_err;
	}

	/* we are on the idr, now get on the inode */
	ret = fsnotify_add_inode_mark_locked(&tmp_i_mark->fsn_mark, inode, 0);
	if (ret) {
		/* we failed to get on the inode, get off the idr */
		inotify_remove_from_idr(group, tmp_i_mark);
		goto out_err;
	}


	/* return the watch descriptor for this new mark */
	ret = tmp_i_mark->wd;

out_err:
	/* match the ref from fsnotify_init_mark() */
	fsnotify_put_mark(&tmp_i_mark->fsn_mark);

	return ret;
}