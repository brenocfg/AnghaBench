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
struct fsnotify_mark {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_marks; } ;
struct fsnotify_group {TYPE_1__ fanotify_data; int /*<<< orphan*/  num_marks; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct fsnotify_mark* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fanotify_mark_cache ; 
 int fsnotify_add_mark_locked (struct fsnotify_mark*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_init_mark (struct fsnotify_mark*,struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 struct fsnotify_mark* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fsnotify_mark *fanotify_add_new_mark(struct fsnotify_group *group,
						   fsnotify_connp_t *connp,
						   unsigned int type,
						   __kernel_fsid_t *fsid)
{
	struct fsnotify_mark *mark;
	int ret;

	if (atomic_read(&group->num_marks) > group->fanotify_data.max_marks)
		return ERR_PTR(-ENOSPC);

	mark = kmem_cache_alloc(fanotify_mark_cache, GFP_KERNEL);
	if (!mark)
		return ERR_PTR(-ENOMEM);

	fsnotify_init_mark(mark, group);
	ret = fsnotify_add_mark_locked(mark, connp, type, 0, fsid);
	if (ret) {
		fsnotify_put_mark(mark);
		return ERR_PTR(ret);
	}

	return mark;
}