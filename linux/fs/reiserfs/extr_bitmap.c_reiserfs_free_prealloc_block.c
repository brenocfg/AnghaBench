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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_super; int /*<<< orphan*/  t_trans_id; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  _reiserfs_free_block (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_reusable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reiserfs_free_prealloc_block(struct reiserfs_transaction_handle *th,
					 struct inode *inode, b_blocknr_t block)
{
	BUG_ON(!th->t_trans_id);
	RFALSE(!th->t_super,
	       "vs-4060: trying to free block on nonexistent device");
	if (!is_reusable(th->t_super, block, 1))
		return;
	_reiserfs_free_block(th, inode, block, 1);
}