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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {void* lowerdata; void* lower; struct dentry* __upperdentry; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 void* igrab (struct inode*) ; 
 int /*<<< orphan*/  ovl_copyattr (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ovl_copyflags (struct inode*,struct inode*) ; 

void ovl_inode_init(struct inode *inode, struct dentry *upperdentry,
		    struct dentry *lowerdentry, struct dentry *lowerdata)
{
	struct inode *realinode = d_inode(upperdentry ?: lowerdentry);

	if (upperdentry)
		OVL_I(inode)->__upperdentry = upperdentry;
	if (lowerdentry)
		OVL_I(inode)->lower = igrab(d_inode(lowerdentry));
	if (lowerdata)
		OVL_I(inode)->lowerdata = igrab(d_inode(lowerdata));

	ovl_copyattr(realinode, inode);
	ovl_copyflags(realinode, inode);
	if (!inode->i_ino)
		inode->i_ino = realinode->i_ino;
}