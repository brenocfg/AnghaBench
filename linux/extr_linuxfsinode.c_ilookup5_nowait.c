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
struct inode {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* find_inode (struct super_block*,struct hlist_head*,int (*) (struct inode*,void*),void*) ; 
 int hash (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  inode_hash_lock ; 
 struct hlist_head* inode_hashtable ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct inode *ilookup5_nowait(struct super_block *sb, unsigned long hashval,
		int (*test)(struct inode *, void *), void *data)
{
	struct hlist_head *head = inode_hashtable + hash(sb, hashval);
	struct inode *inode;

	spin_lock(&inode_hash_lock);
	inode = find_inode(sb, head, test, data);
	spin_unlock(&inode_hash_lock);

	return IS_ERR(inode) ? NULL : inode;
}