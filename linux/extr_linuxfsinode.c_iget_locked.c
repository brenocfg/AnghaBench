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
struct inode {unsigned long i_ino; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_hash; int /*<<< orphan*/  i_state; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  I_NEW ; 
 struct inode* alloc_inode (struct super_block*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 struct inode* find_inode_fast (struct super_block*,struct hlist_head*,unsigned long) ; 
 int hash (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  inode_hash_lock ; 
 struct hlist_head* inode_hashtable ; 
 int /*<<< orphan*/  inode_sb_list_add (struct inode*) ; 
 int /*<<< orphan*/  inode_unhashed (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_inode (struct inode*) ; 

struct inode *iget_locked(struct super_block *sb, unsigned long ino)
{
	struct hlist_head *head = inode_hashtable + hash(sb, ino);
	struct inode *inode;
again:
	spin_lock(&inode_hash_lock);
	inode = find_inode_fast(sb, head, ino);
	spin_unlock(&inode_hash_lock);
	if (inode) {
		if (IS_ERR(inode))
			return NULL;
		wait_on_inode(inode);
		if (unlikely(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
		return inode;
	}

	inode = alloc_inode(sb);
	if (inode) {
		struct inode *old;

		spin_lock(&inode_hash_lock);
		/* We released the lock, so.. */
		old = find_inode_fast(sb, head, ino);
		if (!old) {
			inode->i_ino = ino;
			spin_lock(&inode->i_lock);
			inode->i_state = I_NEW;
			hlist_add_head(&inode->i_hash, head);
			spin_unlock(&inode->i_lock);
			inode_sb_list_add(inode);
			spin_unlock(&inode_hash_lock);

			/* Return the locked inode with I_NEW set, the
			 * caller is responsible for filling in the contents
			 */
			return inode;
		}

		/*
		 * Uhhuh, somebody else created the same inode under
		 * us. Use the old inode instead of the one we just
		 * allocated.
		 */
		spin_unlock(&inode_hash_lock);
		destroy_inode(inode);
		if (IS_ERR(old))
			return NULL;
		inode = old;
		wait_on_inode(inode);
		if (unlikely(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
	}
	return inode;
}