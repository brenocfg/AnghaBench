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
struct orangefs_inode_s {int /*<<< orphan*/  link_target; } ;
struct inode {int i_mode; } ;
struct ORANGEFS_sys_attr_s {int /*<<< orphan*/  objtype; } ;

/* Variables and functions */
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 int /*<<< orphan*/  ORANGEFS_NAME_MAX ; 
 int S_IFLNK ; 
 int orangefs_inode_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orangefs_make_bad_inode (struct inode*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orangefs_inode_is_stale(struct inode *inode,
    struct ORANGEFS_sys_attr_s *attrs, char *link_target)
{
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	int type = orangefs_inode_type(attrs->objtype);
	/*
	 * If the inode type or symlink target have changed then this
	 * inode is stale.
	 */
	if (type == -1 || !(inode->i_mode & type)) {
		orangefs_make_bad_inode(inode);
		return 1;
	}
	if (type == S_IFLNK && strncmp(orangefs_inode->link_target,
	    link_target, ORANGEFS_NAME_MAX)) {
		orangefs_make_bad_inode(inode);
		return 1;
	}
	return 0;
}