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
struct the_nilfs {int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_sem; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_nilfs (struct the_nilfs*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_cleanup_super (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_detach_log_writer (struct super_block*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_put_super(struct super_block *sb)
{
	struct the_nilfs *nilfs = sb->s_fs_info;

	nilfs_detach_log_writer(sb);

	if (!sb_rdonly(sb)) {
		down_write(&nilfs->ns_sem);
		nilfs_cleanup_super(sb);
		up_write(&nilfs->ns_sem);
	}

	iput(nilfs->ns_sufile);
	iput(nilfs->ns_cpfile);
	iput(nilfs->ns_dat);

	destroy_nilfs(nilfs);
	sb->s_fs_info = NULL;
}