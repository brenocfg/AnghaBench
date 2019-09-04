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
struct fsnotify_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int IN_CLOEXEC ; 
 int IN_NONBLOCK ; 
 scalar_t__ IS_ERR (struct fsnotify_group*) ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int PTR_ERR (struct fsnotify_group*) ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct fsnotify_group*,int) ; 
 int /*<<< orphan*/  fsnotify_destroy_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  inotify_fops ; 
 int /*<<< orphan*/  inotify_max_queued_events ; 
 struct fsnotify_group* inotify_new_group (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_inotify_init(int flags)
{
	struct fsnotify_group *group;
	int ret;

	/* Check the IN_* constants for consistency.  */
	BUILD_BUG_ON(IN_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(IN_NONBLOCK != O_NONBLOCK);

	if (flags & ~(IN_CLOEXEC | IN_NONBLOCK))
		return -EINVAL;

	/* fsnotify_obtain_group took a reference to group, we put this when we kill the file in the end */
	group = inotify_new_group(inotify_max_queued_events);
	if (IS_ERR(group))
		return PTR_ERR(group);

	ret = anon_inode_getfd("inotify", &inotify_fops, group,
				  O_RDONLY | flags);
	if (ret < 0)
		fsnotify_destroy_group(group);

	return ret;
}