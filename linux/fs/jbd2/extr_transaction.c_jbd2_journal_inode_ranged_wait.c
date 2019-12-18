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
struct jbd2_inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  JI_WAIT_DATA ; 
 int jbd2_journal_file_inode (int /*<<< orphan*/ *,struct jbd2_inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int jbd2_journal_inode_ranged_wait(handle_t *handle, struct jbd2_inode *jinode,
		loff_t start_byte, loff_t length)
{
	return jbd2_journal_file_inode(handle, jinode, JI_WAIT_DATA,
			start_byte, start_byte + length - 1);
}