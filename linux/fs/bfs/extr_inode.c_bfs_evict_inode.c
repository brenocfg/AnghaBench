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
struct inode {unsigned long i_ino; scalar_t__ i_nlink; int /*<<< orphan*/  i_data; struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
struct bfs_sb_info {scalar_t__ si_lf_eblk; int /*<<< orphan*/  bfs_lock; int /*<<< orphan*/  si_imap; int /*<<< orphan*/  si_freei; int /*<<< orphan*/  si_freeb; } ;
struct bfs_inode_info {scalar_t__ i_sblock; scalar_t__ i_eblock; scalar_t__ i_dsk_ino; } ;
struct bfs_inode {int dummy; } ;

/* Variables and functions */
 struct bfs_inode_info* BFS_I (struct inode*) ; 
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct bfs_inode*) ; 
 int /*<<< orphan*/  bfs_dump_imap (char*,struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned long) ; 
 struct bfs_inode* find_inode (struct super_block*,unsigned long,struct buffer_head**) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (struct bfs_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfs_evict_inode(struct inode *inode)
{
	unsigned long ino = inode->i_ino;
	struct bfs_inode *di;
	struct buffer_head *bh;
	struct super_block *s = inode->i_sb;
	struct bfs_sb_info *info = BFS_SB(s);
	struct bfs_inode_info *bi = BFS_I(inode);

	dprintf("ino=%08lx\n", ino);

	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode);
	clear_inode(inode);

	if (inode->i_nlink)
		return;

	di = find_inode(s, inode->i_ino, &bh);
	if (IS_ERR(di))
		return;

	mutex_lock(&info->bfs_lock);
	/* clear on-disk inode */
	memset(di, 0, sizeof(struct bfs_inode));
	mark_buffer_dirty(bh);
	brelse(bh);

	if (bi->i_dsk_ino) {
		if (bi->i_sblock)
			info->si_freeb += bi->i_eblock + 1 - bi->i_sblock;
		info->si_freei++;
		clear_bit(ino, info->si_imap);
		bfs_dump_imap("evict_inode", s);
	}

	/*
	 * If this was the last file, make the previous block
	 * "last block of the last file" even if there is no
	 * real file there, saves us 1 gap.
	 */
	if (info->si_lf_eblk == bi->i_eblock)
		info->si_lf_eblk = bi->i_sblock - 1;
	mutex_unlock(&info->bfs_lock);
}