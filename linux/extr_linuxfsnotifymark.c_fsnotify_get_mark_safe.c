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
struct fsnotify_mark {int flags; int /*<<< orphan*/  lock; TYPE_1__* group; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_waits; } ;

/* Variables and functions */
 int FSNOTIFY_MARK_FLAG_ATTACHED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fsnotify_get_mark_safe(struct fsnotify_mark *mark)
{
	if (!mark)
		return true;

	if (refcount_inc_not_zero(&mark->refcnt)) {
		spin_lock(&mark->lock);
		if (mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED) {
			/* mark is attached, group is still alive then */
			atomic_inc(&mark->group->user_waits);
			spin_unlock(&mark->lock);
			return true;
		}
		spin_unlock(&mark->lock);
		fsnotify_put_mark(mark);
	}
	return false;
}