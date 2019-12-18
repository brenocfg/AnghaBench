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
struct fsnotify_mark {int /*<<< orphan*/  connector; } ;
struct fsnotify_group {int /*<<< orphan*/  mark_mutex; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;
typedef  int __u32 ;

/* Variables and functions */
 int ENOENT ; 
 int fanotify_mark_remove_from_mask (struct fsnotify_mark*,int,unsigned int,int*) ; 
 int fsnotify_conn_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_detach_mark (struct fsnotify_mark*) ; 
 struct fsnotify_mark* fsnotify_find_mark (int /*<<< orphan*/ *,struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_free_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_recalc_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fanotify_remove_mark(struct fsnotify_group *group,
				fsnotify_connp_t *connp, __u32 mask,
				unsigned int flags)
{
	struct fsnotify_mark *fsn_mark = NULL;
	__u32 removed;
	int destroy_mark;

	mutex_lock(&group->mark_mutex);
	fsn_mark = fsnotify_find_mark(connp, group);
	if (!fsn_mark) {
		mutex_unlock(&group->mark_mutex);
		return -ENOENT;
	}

	removed = fanotify_mark_remove_from_mask(fsn_mark, mask, flags,
						 &destroy_mark);
	if (removed & fsnotify_conn_mask(fsn_mark->connector))
		fsnotify_recalc_mask(fsn_mark->connector);
	if (destroy_mark)
		fsnotify_detach_mark(fsn_mark);
	mutex_unlock(&group->mark_mutex);
	if (destroy_mark)
		fsnotify_free_mark(fsn_mark);

	/* matches the fsnotify_find_mark() */
	fsnotify_put_mark(fsn_mark);
	return 0;
}