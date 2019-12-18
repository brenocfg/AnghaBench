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
struct inode {int i_state; } ;
struct erofs_inode {int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  erofs_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 int erofs_fill_inode (struct inode*,int) ; 
 struct inode* erofs_iget_locked (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *erofs_iget(struct super_block *sb,
			 erofs_nid_t nid,
			 bool isdir)
{
	struct inode *inode = erofs_iget_locked(sb, nid);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (inode->i_state & I_NEW) {
		int err;
		struct erofs_inode *vi = EROFS_I(inode);

		vi->nid = nid;

		err = erofs_fill_inode(inode, isdir);
		if (!err)
			unlock_new_inode(inode);
		else {
			iget_failed(inode);
			inode = ERR_PTR(err);
		}
	}
	return inode;
}