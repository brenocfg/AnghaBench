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
struct fsnotify_mark {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  g_list; int /*<<< orphan*/  connector; scalar_t__ mask; struct fsnotify_group* group; } ;
struct fsnotify_group {int /*<<< orphan*/  num_marks; int /*<<< orphan*/  marks_list; int /*<<< orphan*/  mark_mutex; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FSNOTIFY_MARK_FLAG_ALIVE ; 
 int FSNOTIFY_MARK_FLAG_ATTACHED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int fsnotify_add_mark_list (struct fsnotify_mark*,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_get_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_recalc_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int fsnotify_add_mark_locked(struct fsnotify_mark *mark,
			     fsnotify_connp_t *connp, unsigned int type,
			     int allow_dups, __kernel_fsid_t *fsid)
{
	struct fsnotify_group *group = mark->group;
	int ret = 0;

	BUG_ON(!mutex_is_locked(&group->mark_mutex));

	/*
	 * LOCKING ORDER!!!!
	 * group->mark_mutex
	 * mark->lock
	 * mark->connector->lock
	 */
	spin_lock(&mark->lock);
	mark->flags |= FSNOTIFY_MARK_FLAG_ALIVE | FSNOTIFY_MARK_FLAG_ATTACHED;

	list_add(&mark->g_list, &group->marks_list);
	atomic_inc(&group->num_marks);
	fsnotify_get_mark(mark); /* for g_list */
	spin_unlock(&mark->lock);

	ret = fsnotify_add_mark_list(mark, connp, type, allow_dups, fsid);
	if (ret)
		goto err;

	if (mark->mask)
		fsnotify_recalc_mask(mark->connector);

	return ret;
err:
	spin_lock(&mark->lock);
	mark->flags &= ~(FSNOTIFY_MARK_FLAG_ALIVE |
			 FSNOTIFY_MARK_FLAG_ATTACHED);
	list_del_init(&mark->g_list);
	spin_unlock(&mark->lock);
	atomic_dec(&group->num_marks);

	fsnotify_put_mark(mark);
	return ret;
}