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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_IGET_SPECIAL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* ext4_iget (struct super_block*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 

__attribute__((used)) static struct inode *ext4_get_journal_inode(struct super_block *sb,
					     unsigned int journal_inum)
{
	struct inode *journal_inode;

	/*
	 * Test for the existence of a valid inode on disk.  Bad things
	 * happen if we iget() an unused inode, as the subsequent iput()
	 * will try to delete it.
	 */
	journal_inode = ext4_iget(sb, journal_inum, EXT4_IGET_SPECIAL);
	if (IS_ERR(journal_inode)) {
		ext4_msg(sb, KERN_ERR, "no journal found");
		return NULL;
	}
	if (!journal_inode->i_nlink) {
		make_bad_inode(journal_inode);
		iput(journal_inode);
		ext4_msg(sb, KERN_ERR, "journal inode is deleted");
		return NULL;
	}

	jbd_debug(2, "Journal inode found at %p: %lld bytes\n",
		  journal_inode, journal_inode->i_size);
	if (!S_ISREG(journal_inode->i_mode)) {
		ext4_msg(sb, KERN_ERR, "invalid journal inode");
		iput(journal_inode);
		return NULL;
	}
	return journal_inode;
}