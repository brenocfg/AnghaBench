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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct inode {int i_state; scalar_t__ i_ino; } ;
struct ceph_vino {int /*<<< orphan*/  snap; int /*<<< orphan*/  ino; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
 int /*<<< orphan*/  ceph_ino_compare ; 
 int /*<<< orphan*/  ceph_set_ino_cb ; 
 int /*<<< orphan*/  ceph_vino_to_ino (struct ceph_vino) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceph_vino*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ceph_get_inode(struct super_block *sb, struct ceph_vino vino)
{
	struct inode *inode;
	ino_t t = ceph_vino_to_ino(vino);

	inode = iget5_locked(sb, t, ceph_ino_compare, ceph_set_ino_cb, &vino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (inode->i_state & I_NEW) {
		dout("get_inode created new inode %p %llx.%llx ino %llx\n",
		     inode, ceph_vinop(inode), (u64)inode->i_ino);
		unlock_new_inode(inode);
	}

	dout("get_inode on %lu=%llx.%llx got %p\n", inode->i_ino, vino.ino,
	     vino.snap, inode);
	return inode;
}