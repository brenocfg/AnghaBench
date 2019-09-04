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
struct fsnotify_mark {int dummy; } ;
struct fsnotify_group {int /*<<< orphan*/  mark_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  fsnotify_detach_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_free_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fsnotify_destroy_mark(struct fsnotify_mark *mark,
			   struct fsnotify_group *group)
{
	mutex_lock_nested(&group->mark_mutex, SINGLE_DEPTH_NESTING);
	fsnotify_detach_mark(mark);
	mutex_unlock(&group->mark_mutex);
	fsnotify_free_mark(mark);
}