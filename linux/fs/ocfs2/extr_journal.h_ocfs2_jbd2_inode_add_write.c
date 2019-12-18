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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_jinode; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int jbd2_journal_inode_ranged_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_jbd2_inode_add_write(handle_t *handle, struct inode *inode,
					     loff_t start_byte, loff_t length)
{
	return jbd2_journal_inode_ranged_write(handle,
					       &OCFS2_I(inode)->ip_jinode,
					       start_byte, length);
}