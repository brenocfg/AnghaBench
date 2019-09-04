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
struct super_block {int s_blocksize; } ;
struct minix_sb_info {int s_imap_blocks; unsigned long s_ninodes; struct buffer_head** s_imap; } ;
struct inode {unsigned long i_ino; scalar_t__ i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  bitmap_lock ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned long minix_find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* minix_i (struct inode*) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 scalar_t__ minix_test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct inode *minix_new_inode(const struct inode *dir, umode_t mode, int *error)
{
	struct super_block *sb = dir->i_sb;
	struct minix_sb_info *sbi = minix_sb(sb);
	struct inode *inode = new_inode(sb);
	struct buffer_head * bh;
	int bits_per_zone = 8 * sb->s_blocksize;
	unsigned long j;
	int i;

	if (!inode) {
		*error = -ENOMEM;
		return NULL;
	}
	j = bits_per_zone;
	bh = NULL;
	*error = -ENOSPC;
	spin_lock(&bitmap_lock);
	for (i = 0; i < sbi->s_imap_blocks; i++) {
		bh = sbi->s_imap[i];
		j = minix_find_first_zero_bit(bh->b_data, bits_per_zone);
		if (j < bits_per_zone)
			break;
	}
	if (!bh || j >= bits_per_zone) {
		spin_unlock(&bitmap_lock);
		iput(inode);
		return NULL;
	}
	if (minix_test_and_set_bit(j, bh->b_data)) {	/* shouldn't happen */
		spin_unlock(&bitmap_lock);
		printk("minix_new_inode: bit already set\n");
		iput(inode);
		return NULL;
	}
	spin_unlock(&bitmap_lock);
	mark_buffer_dirty(bh);
	j += i * bits_per_zone;
	if (!j || j > sbi->s_ninodes) {
		iput(inode);
		return NULL;
	}
	inode_init_owner(inode, dir, mode);
	inode->i_ino = j;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_blocks = 0;
	memset(&minix_i(inode)->u, 0, sizeof(minix_i(inode)->u));
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	*error = 0;
	return inode;
}