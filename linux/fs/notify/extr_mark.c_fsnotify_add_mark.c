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
struct fsnotify_group {int /*<<< orphan*/  mark_mutex; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;

/* Variables and functions */
 int fsnotify_add_mark_locked (struct fsnotify_mark*,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fsnotify_add_mark(struct fsnotify_mark *mark, fsnotify_connp_t *connp,
		      unsigned int type, int allow_dups, __kernel_fsid_t *fsid)
{
	int ret;
	struct fsnotify_group *group = mark->group;

	mutex_lock(&group->mark_mutex);
	ret = fsnotify_add_mark_locked(mark, connp, type, allow_dups, fsid);
	mutex_unlock(&group->mark_mutex);
	return ret;
}