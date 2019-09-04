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
struct the_nilfs {int ns_mount_opt; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {int dummy; } ;

/* Variables and functions */
 int NILFS_MOUNT_BARRIER ; 
 int NILFS_MOUNT_ERRORS_RO ; 

__attribute__((used)) static inline void
nilfs_set_default_options(struct super_block *sb,
			  struct nilfs_super_block *sbp)
{
	struct the_nilfs *nilfs = sb->s_fs_info;

	nilfs->ns_mount_opt =
		NILFS_MOUNT_ERRORS_RO | NILFS_MOUNT_BARRIER;
}