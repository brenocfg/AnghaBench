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
struct fsnotify_group {int /*<<< orphan*/  q_len; int /*<<< orphan*/  notification_lock; } ;
struct fsnotify_event {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void fsnotify_remove_queued_event(struct fsnotify_group *group,
				  struct fsnotify_event *event)
{
	assert_spin_locked(&group->notification_lock);
	/*
	 * We need to init list head for the case of overflow event so that
	 * check in fsnotify_add_event() works
	 */
	list_del_init(&event->list);
	group->q_len--;
}