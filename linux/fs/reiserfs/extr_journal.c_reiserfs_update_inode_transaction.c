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
struct reiserfs_journal {int /*<<< orphan*/  j_trans_id; int /*<<< orphan*/  j_current_jl; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_trans_id; int /*<<< orphan*/  i_jl; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 

void reiserfs_update_inode_transaction(struct inode *inode)
{
	struct reiserfs_journal *journal = SB_JOURNAL(inode->i_sb);
	REISERFS_I(inode)->i_jl = journal->j_current_jl;
	REISERFS_I(inode)->i_trans_id = journal->j_trans_id;
}