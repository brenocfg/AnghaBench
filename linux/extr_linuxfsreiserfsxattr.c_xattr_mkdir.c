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
struct inode {TYPE_1__* i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* mkdir ) (struct inode*,struct dentry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int stub1 (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xattr_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	BUG_ON(!inode_is_locked(dir));
	return dir->i_op->mkdir(dir, dentry, mode);
}