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
struct fsnotify_mark {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  g_list; int /*<<< orphan*/  refcnt; struct fsnotify_group* group; } ;
struct fsnotify_group {int /*<<< orphan*/  num_marks; int /*<<< orphan*/  mark_mutex; } ;

/* Variables and functions */
 int FSNOTIFY_MARK_FLAG_ATTACHED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_mark_srcu ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_lock_held (int /*<<< orphan*/ *) ; 

void fsnotify_detach_mark(struct fsnotify_mark *mark)
{
	struct fsnotify_group *group = mark->group;

	WARN_ON_ONCE(!mutex_is_locked(&group->mark_mutex));
	WARN_ON_ONCE(!srcu_read_lock_held(&fsnotify_mark_srcu) &&
		     refcount_read(&mark->refcnt) < 1 +
			!!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED));

	spin_lock(&mark->lock);
	/* something else already called this function on this mark */
	if (!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED)) {
		spin_unlock(&mark->lock);
		return;
	}
	mark->flags &= ~FSNOTIFY_MARK_FLAG_ATTACHED;
	list_del_init(&mark->g_list);
	spin_unlock(&mark->lock);

	atomic_dec(&group->num_marks);

	/* Drop mark reference acquired in fsnotify_add_mark_locked() */
	fsnotify_put_mark(mark);
}