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
struct super_block {int /*<<< orphan*/  s_fsnotify_marks; } ;
struct fsnotify_group {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSNOTIFY_OBJ_TYPE_SB ; 
 int fanotify_add_mark (struct fsnotify_group*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fanotify_add_sb_mark(struct fsnotify_group *group,
				struct super_block *sb, __u32 mask,
				unsigned int flags, __kernel_fsid_t *fsid)
{
	return fanotify_add_mark(group, &sb->s_fsnotify_marks,
				 FSNOTIFY_OBJ_TYPE_SB, mask, flags, fsid);
}