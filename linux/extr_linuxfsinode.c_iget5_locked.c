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
struct inode {scalar_t__ i_state; } ;

/* Variables and functions */
 struct inode* alloc_inode (struct super_block*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 struct inode* ilookup5 (struct super_block*,unsigned long,int (*) (struct inode*,void*),void*) ; 
 struct inode* inode_insert5 (struct inode*,unsigned long,int (*) (struct inode*,void*),int (*) (struct inode*,void*),void*) ; 
 scalar_t__ unlikely (int) ; 

struct inode *iget5_locked(struct super_block *sb, unsigned long hashval,
		int (*test)(struct inode *, void *),
		int (*set)(struct inode *, void *), void *data)
{
	struct inode *inode = ilookup5(sb, hashval, test, data);

	if (!inode) {
		struct inode *new = alloc_inode(sb);

		if (new) {
			new->i_state = 0;
			inode = inode_insert5(new, hashval, test, set, data);
			if (unlikely(inode != new))
				destroy_inode(new);
		}
	}
	return inode;
}