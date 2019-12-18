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
struct fsnotify_group {scalar_t__ overflow_event; TYPE_1__* ops; int /*<<< orphan*/  user_waits; int /*<<< orphan*/  notification_waitq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_event ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FSNOTIFY_OBJ_ALL_TYPES_MASK ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_clear_marks_by_group (struct fsnotify_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_flush_notify (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_group_stop_queueing (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_put_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_wait_marks_destroyed () ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void fsnotify_destroy_group(struct fsnotify_group *group)
{
	/*
	 * Stop queueing new events. The code below is careful enough to not
	 * require this but fanotify needs to stop queuing events even before
	 * fsnotify_destroy_group() is called and this makes the other callers
	 * of fsnotify_destroy_group() to see the same behavior.
	 */
	fsnotify_group_stop_queueing(group);

	/* Clear all marks for this group and queue them for destruction */
	fsnotify_clear_marks_by_group(group, FSNOTIFY_OBJ_ALL_TYPES_MASK);

	/*
	 * Some marks can still be pinned when waiting for response from
	 * userspace. Wait for those now. fsnotify_prepare_user_wait() will
	 * not succeed now so this wait is race-free.
	 */
	wait_event(group->notification_waitq, !atomic_read(&group->user_waits));

	/*
	 * Wait until all marks get really destroyed. We could actually destroy
	 * them ourselves instead of waiting for worker to do it, however that
	 * would be racy as worker can already be processing some marks before
	 * we even entered fsnotify_destroy_group().
	 */
	fsnotify_wait_marks_destroyed();

	/*
	 * Since we have waited for fsnotify_mark_srcu in
	 * fsnotify_mark_destroy_list() there can be no outstanding event
	 * notification against this group. So clearing the notification queue
	 * of all events is reliable now.
	 */
	fsnotify_flush_notify(group);

	/*
	 * Destroy overflow event (we cannot use fsnotify_destroy_event() as
	 * that deliberately ignores overflow events.
	 */
	if (group->overflow_event)
		group->ops->free_event(group->overflow_event);

	fsnotify_put_group(group);
}