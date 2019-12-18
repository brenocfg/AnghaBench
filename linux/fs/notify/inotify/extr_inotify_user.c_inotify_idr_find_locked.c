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
struct fsnotify_mark {int /*<<< orphan*/  refcnt; } ;
struct inotify_inode_mark {struct fsnotify_mark fsn_mark; } ;
struct idr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_lock; struct idr idr; } ;
struct fsnotify_group {TYPE_1__ inotify_data; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_get_mark (struct fsnotify_mark*) ; 
 struct inotify_inode_mark* idr_find (struct idr*,int) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inotify_inode_mark *inotify_idr_find_locked(struct fsnotify_group *group,
								int wd)
{
	struct idr *idr = &group->inotify_data.idr;
	spinlock_t *idr_lock = &group->inotify_data.idr_lock;
	struct inotify_inode_mark *i_mark;

	assert_spin_locked(idr_lock);

	i_mark = idr_find(idr, wd);
	if (i_mark) {
		struct fsnotify_mark *fsn_mark = &i_mark->fsn_mark;

		fsnotify_get_mark(fsn_mark);
		/* One ref for being in the idr, one ref we just took */
		BUG_ON(refcount_read(&fsn_mark->refcnt) < 2);
	}

	return i_mark;
}