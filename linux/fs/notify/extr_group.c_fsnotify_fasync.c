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
struct fsnotify_group {int /*<<< orphan*/  fsn_fa; } ;
struct file {struct fsnotify_group* private_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

int fsnotify_fasync(int fd, struct file *file, int on)
{
	struct fsnotify_group *group = file->private_data;

	return fasync_helper(fd, file, on, &group->fsn_fa) >= 0 ? 0 : -EIO;
}