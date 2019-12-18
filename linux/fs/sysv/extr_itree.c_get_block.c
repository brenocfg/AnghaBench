#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_7__ {int /*<<< orphan*/  bh; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int DEPTH ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 int alloc_branch (struct inode*,int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  block_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int block_to_path (struct inode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_branch (struct inode*,int,int*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointers_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ splice_branch (struct inode*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
{
	int err = -EIO;
	int offsets[DEPTH];
	Indirect chain[DEPTH];
	struct super_block *sb = inode->i_sb;
	Indirect *partial;
	int left;
	int depth = block_to_path(inode, iblock, offsets);

	if (depth == 0)
		goto out;

reread:
	read_lock(&pointers_lock);
	partial = get_branch(inode, depth, offsets, chain, &err);
	read_unlock(&pointers_lock);

	/* Simplest case - block found, no allocation needed */
	if (!partial) {
got_it:
		map_bh(bh_result, sb, block_to_cpu(SYSV_SB(sb),
					chain[depth-1].key));
		/* Clean up and exit */
		partial = chain+depth-1; /* the whole chain */
		goto cleanup;
	}

	/* Next simple case - plain lookup or failed read of indirect block */
	if (!create || err == -EIO) {
cleanup:
		while (partial > chain) {
			brelse(partial->bh);
			partial--;
		}
out:
		return err;
	}

	/*
	 * Indirect block might be removed by truncate while we were
	 * reading it. Handling of that case (forget what we've got and
	 * reread) is taken out of the main path.
	 */
	if (err == -EAGAIN)
		goto changed;

	left = (chain + depth) - partial;
	err = alloc_branch(inode, left, offsets+(partial-chain), partial);
	if (err)
		goto cleanup;

	if (splice_branch(inode, chain, partial, left) < 0)
		goto changed;

	set_buffer_new(bh_result);
	goto got_it;

changed:
	while (partial > chain) {
		brelse(partial->bh);
		partial--;
	}
	goto reread;
}