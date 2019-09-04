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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  squashfs_iget (struct super_block*,long long,unsigned int) ; 
 long long squashfs_inode_lookup (struct super_block*,unsigned int) ; 

__attribute__((used)) static struct dentry *squashfs_export_iget(struct super_block *sb,
	unsigned int ino_num)
{
	long long ino;
	struct dentry *dentry = ERR_PTR(-ENOENT);

	TRACE("Entered squashfs_export_iget\n");

	ino = squashfs_inode_lookup(sb, ino_num);
	if (ino >= 0)
		dentry = d_obtain_alias(squashfs_iget(sb, ino, ino_num));

	return dentry;
}