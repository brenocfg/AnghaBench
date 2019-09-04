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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_acl_mode; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  FI_ACL_MODE ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_acl_inode(struct inode *inode, umode_t mode)
{
	F2FS_I(inode)->i_acl_mode = mode;
	set_inode_flag(inode, FI_ACL_MODE);
	f2fs_mark_inode_dirty_sync(inode, false);
}