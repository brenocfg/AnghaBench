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
struct treepath {int dummy; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GET_BLOCK_NO_IMUX ; 
 int reiserfs_new_unf_blocknrs (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ *,struct treepath*,int /*<<< orphan*/ ) ; 
 int reiserfs_new_unf_blocknrs2 (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ *,struct treepath*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _allocate_block(struct reiserfs_transaction_handle *th,
				  sector_t block,
				  struct inode *inode,
				  b_blocknr_t * allocated_block_nr,
				  struct treepath *path, int flags)
{
	BUG_ON(!th->t_trans_id);

#ifdef REISERFS_PREALLOCATE
	if (!(flags & GET_BLOCK_NO_IMUX)) {
		return reiserfs_new_unf_blocknrs2(th, inode, allocated_block_nr,
						  path, block);
	}
#endif
	return reiserfs_new_unf_blocknrs(th, inode, allocated_block_nr, path,
					 block);
}