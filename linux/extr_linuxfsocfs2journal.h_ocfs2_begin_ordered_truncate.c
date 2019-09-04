#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  ip_jinode; } ;
struct TYPE_5__ {TYPE_1__* journal; } ;
struct TYPE_4__ {int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 TYPE_3__* OCFS2_I (struct inode*) ; 
 TYPE_2__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int jbd2_journal_begin_ordered_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_begin_ordered_truncate(struct inode *inode,
					       loff_t new_size)
{
	return jbd2_journal_begin_ordered_truncate(
				OCFS2_SB(inode->i_sb)->journal->j_journal,
				&OCFS2_I(inode)->ip_jinode,
				new_size);
}