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
typedef  int /*<<< orphan*/  tid_t ;
struct super_block {int dummy; } ;
struct jfs_superblock {int /*<<< orphan*/  s_flag; } ;
struct inode {int /*<<< orphan*/  i_size; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {int mntflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_FORCE ; 
 int /*<<< orphan*/  FILESYSTEM_I ; 
 int JFS_BAD_SAIT ; 
 TYPE_1__* JFS_SBI (struct super_block*) ; 
 scalar_t__ PSIZE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  diFreeSpecial (struct inode*) ; 
 struct inode* diReadSpecial (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ readSuper (struct super_block*,struct buffer_head**) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 scalar_t__ xtInsert (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void duplicateIXtree(struct super_block *sb, s64 blkno,
			    int xlen, s64 *xaddr)
{
	struct jfs_superblock *j_sb;
	struct buffer_head *bh;
	struct inode *ip;
	tid_t tid;

	/* if AIT2 ipmap2 is bad, do not try to update it */
	if (JFS_SBI(sb)->mntflag & JFS_BAD_SAIT)	/* s_flag */
		return;
	ip = diReadSpecial(sb, FILESYSTEM_I, 1);
	if (ip == NULL) {
		JFS_SBI(sb)->mntflag |= JFS_BAD_SAIT;
		if (readSuper(sb, &bh))
			return;
		j_sb = (struct jfs_superblock *)bh->b_data;
		j_sb->s_flag |= cpu_to_le32(JFS_BAD_SAIT);

		mark_buffer_dirty(bh);
		sync_dirty_buffer(bh);
		brelse(bh);
		return;
	}

	/* start transaction */
	tid = txBegin(sb, COMMIT_FORCE);
	/* update the inode map addressing structure to point to it */
	if (xtInsert(tid, ip, 0, blkno, xlen, xaddr, 0)) {
		JFS_SBI(sb)->mntflag |= JFS_BAD_SAIT;
		txAbort(tid, 1);
		goto cleanup;

	}
	/* update the inode map's inode to reflect the extension */
	ip->i_size += PSIZE;
	inode_add_bytes(ip, PSIZE);
	txCommit(tid, 1, &ip, COMMIT_FORCE);
      cleanup:
	txEnd(tid);
	diFreeSpecial(ip);
}