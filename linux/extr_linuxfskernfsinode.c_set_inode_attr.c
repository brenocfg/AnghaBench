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
struct super_block {int /*<<< orphan*/  s_time_gran; } ;
struct inode {void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct iattr {int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;

/* Variables and functions */
 void* timespec64_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_inode_attr(struct inode *inode, struct iattr *iattr)
{
	struct super_block *sb = inode->i_sb;
	inode->i_uid = iattr->ia_uid;
	inode->i_gid = iattr->ia_gid;
	inode->i_atime = timespec64_trunc(iattr->ia_atime, sb->s_time_gran);
	inode->i_mtime = timespec64_trunc(iattr->ia_mtime, sb->s_time_gran);
	inode->i_ctime = timespec64_trunc(iattr->ia_ctime, sb->s_time_gran);
}