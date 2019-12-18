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
struct orangefs_object_kref {int /*<<< orphan*/  fs_id; int /*<<< orphan*/  khandle; } ;
struct inode {int i_state; unsigned long i_ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int I_NEW ; 
 int /*<<< orphan*/  ORANGEFS_GETATTR_NEW ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct orangefs_object_kref*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 unsigned long orangefs_handle_hash (struct orangefs_object_kref*) ; 
 int /*<<< orphan*/  orangefs_init_iops (struct inode*) ; 
 int orangefs_inode_getattr (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orangefs_set_inode ; 
 int /*<<< orphan*/  orangefs_test_inode ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *orangefs_iget(struct super_block *sb,
		struct orangefs_object_kref *ref)
{
	struct inode *inode = NULL;
	unsigned long hash;
	int error;

	hash = orangefs_handle_hash(ref);
	inode = iget5_locked(sb,
			hash,
			orangefs_test_inode,
			orangefs_set_inode,
			ref);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (!(inode->i_state & I_NEW))
		return inode;

	error = orangefs_inode_getattr(inode, ORANGEFS_GETATTR_NEW);
	if (error) {
		iget_failed(inode);
		return ERR_PTR(error);
	}

	inode->i_ino = hash;	/* needed for stat etc */
	orangefs_init_iops(inode);
	unlock_new_inode(inode);

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "iget handle %pU, fsid %d hash %ld i_ino %lu\n",
		     &ref->khandle,
		     ref->fs_id,
		     hash,
		     inode->i_ino);

	return inode;
}