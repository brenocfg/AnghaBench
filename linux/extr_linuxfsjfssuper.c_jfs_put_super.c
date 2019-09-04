#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct jfs_sb_info {TYPE_1__* direct_inode; int /*<<< orphan*/  nls_tab; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  jfs_err (char*,int) ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 int /*<<< orphan*/  jfs_quota_off_umount (struct super_block*) ; 
 int jfs_umount (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct jfs_sb_info*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jfs_put_super(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	int rc;

	jfs_info("In jfs_put_super");

	jfs_quota_off_umount(sb);

	rc = jfs_umount(sb);
	if (rc)
		jfs_err("jfs_umount failed with return code %d", rc);

	unload_nls(sbi->nls_tab);

	truncate_inode_pages(sbi->direct_inode->i_mapping, 0);
	iput(sbi->direct_inode);

	kfree(sbi);
}