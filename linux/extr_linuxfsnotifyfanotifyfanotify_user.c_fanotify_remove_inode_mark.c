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
struct inode {int /*<<< orphan*/  i_fsnotify_marks; } ;
struct fsnotify_group {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int fanotify_remove_mark (struct fsnotify_group*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int fanotify_remove_inode_mark(struct fsnotify_group *group,
				      struct inode *inode, __u32 mask,
				      unsigned int flags)
{
	return fanotify_remove_mark(group, &inode->i_fsnotify_marks, mask,
				    flags);
}