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
struct super_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SB_MANDLOCK ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int fuse_remount_fs(struct super_block *sb, int *flags, char *data)
{
	sync_filesystem(sb);
	if (*flags & SB_MANDLOCK)
		return -EINVAL;

	return 0;
}