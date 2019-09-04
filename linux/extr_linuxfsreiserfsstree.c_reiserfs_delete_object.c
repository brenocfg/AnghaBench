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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct inode {scalar_t__ i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_delete_solid_item (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ) ; 
 int reiserfs_do_truncate (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int reiserfs_delete_object(struct reiserfs_transaction_handle *th,
			   struct inode *inode)
{
	int err;
	inode->i_size = 0;
	BUG_ON(!th->t_trans_id);

	/* for directory this deletes item containing "." and ".." */
	err =
	    reiserfs_do_truncate(th, inode, NULL, 0 /*no timestamp updates */ );
	if (err)
		return err;

#if defined( USE_INODE_GENERATION_COUNTER )
	if (!old_format_only(th->t_super)) {
		__le32 *inode_generation;

		inode_generation =
		    &REISERFS_SB(th->t_super)->s_rs->s_inode_generation;
		le32_add_cpu(inode_generation, 1);
	}
/* USE_INODE_GENERATION_COUNTER */
#endif
	reiserfs_delete_solid_item(th, inode, INODE_PKEY(inode));

	return err;
}