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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int JI_WAIT_DATA ; 
 int JI_WRITE_DATA ; 
 int jbd2_journal_file_inode (int /*<<< orphan*/ *,struct jbd2_inode*,int) ; 

int jbd2_journal_inode_add_write(handle_t *handle, struct jbd2_inode *jinode)
{
	return jbd2_journal_file_inode(handle, jinode,
				       JI_WRITE_DATA | JI_WAIT_DATA);
}