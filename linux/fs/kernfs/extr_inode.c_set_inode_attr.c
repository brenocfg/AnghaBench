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
struct kernfs_iattrs {int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct inode {void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 void* timestamp_truncate (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static inline void set_inode_attr(struct inode *inode,
				  struct kernfs_iattrs *attrs)
{
	inode->i_uid = attrs->ia_uid;
	inode->i_gid = attrs->ia_gid;
	inode->i_atime = timestamp_truncate(attrs->ia_atime, inode);
	inode->i_mtime = timestamp_truncate(attrs->ia_mtime, inode);
	inode->i_ctime = timestamp_truncate(attrs->ia_ctime, inode);
}