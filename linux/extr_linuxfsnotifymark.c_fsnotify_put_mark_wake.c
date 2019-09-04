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
struct fsnotify_mark {struct fsnotify_group* group; } ;
struct fsnotify_group {int /*<<< orphan*/  notification_waitq; scalar_t__ shutdown; int /*<<< orphan*/  user_waits; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsnotify_put_mark_wake(struct fsnotify_mark *mark)
{
	if (mark) {
		struct fsnotify_group *group = mark->group;

		fsnotify_put_mark(mark);
		/*
		 * We abuse notification_waitq on group shutdown for waiting for
		 * all marks pinned when waiting for userspace.
		 */
		if (atomic_dec_and_test(&group->user_waits) && group->shutdown)
			wake_up(&group->notification_waitq);
	}
}