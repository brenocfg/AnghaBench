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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct fsnotify_group {int /*<<< orphan*/  mark_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 int inotify_new_watch (struct fsnotify_group*,struct inode*,int /*<<< orphan*/ ) ; 
 int inotify_update_existing_watch (struct fsnotify_group*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inotify_update_watch(struct fsnotify_group *group, struct inode *inode, u32 arg)
{
	int ret = 0;

	mutex_lock(&group->mark_mutex);
	/* try to update and existing watch with the new arg */
	ret = inotify_update_existing_watch(group, inode, arg);
	/* no mark present, try to add a new one */
	if (ret == -ENOENT)
		ret = inotify_new_watch(group, inode, arg);
	mutex_unlock(&group->mark_mutex);

	return ret;
}