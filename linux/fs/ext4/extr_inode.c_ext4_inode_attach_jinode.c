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
struct jbd2_inode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_sb; } ;
struct ext4_inode_info {struct jbd2_inode* jinode; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct jbd2_inode* jbd2_alloc_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_free_inode (struct jbd2_inode*) ; 
 int /*<<< orphan*/  jbd2_journal_init_jbd_inode (struct jbd2_inode*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ext4_inode_attach_jinode(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct jbd2_inode *jinode;

	if (ei->jinode || !EXT4_SB(inode->i_sb)->s_journal)
		return 0;

	jinode = jbd2_alloc_inode(GFP_KERNEL);
	spin_lock(&inode->i_lock);
	if (!ei->jinode) {
		if (!jinode) {
			spin_unlock(&inode->i_lock);
			return -ENOMEM;
		}
		ei->jinode = jinode;
		jbd2_journal_init_jbd_inode(ei->jinode, inode);
		jinode = NULL;
	}
	spin_unlock(&inode->i_lock);
	if (unlikely(jinode != NULL))
		jbd2_free_inode(jinode);
	return 0;
}