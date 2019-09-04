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
struct fsnotify_group {int /*<<< orphan*/  notification_lock; } ;
struct fsnotify_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_destroy_event (struct fsnotify_group*,struct fsnotify_event*) ; 
 int /*<<< orphan*/  fsnotify_notify_queue_is_empty (struct fsnotify_group*) ; 
 struct fsnotify_event* fsnotify_remove_first_event (struct fsnotify_group*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fsnotify_flush_notify(struct fsnotify_group *group)
{
	struct fsnotify_event *event;

	spin_lock(&group->notification_lock);
	while (!fsnotify_notify_queue_is_empty(group)) {
		event = fsnotify_remove_first_event(group);
		spin_unlock(&group->notification_lock);
		fsnotify_destroy_event(group, event);
		spin_lock(&group->notification_lock);
	}
	spin_unlock(&group->notification_lock);
}