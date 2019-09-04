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
struct jbd2_inode {int /*<<< orphan*/  i_list; scalar_t__ i_flags; struct inode* i_vfs_inode; int /*<<< orphan*/ * i_next_transaction; int /*<<< orphan*/ * i_transaction; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void jbd2_journal_init_jbd_inode(struct jbd2_inode *jinode, struct inode *inode)
{
	jinode->i_transaction = NULL;
	jinode->i_next_transaction = NULL;
	jinode->i_vfs_inode = inode;
	jinode->i_flags = 0;
	INIT_LIST_HEAD(&jinode->i_list);
}