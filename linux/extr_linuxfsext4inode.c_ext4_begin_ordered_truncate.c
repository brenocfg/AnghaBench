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
struct TYPE_2__ {int /*<<< orphan*/  jinode; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_JOURNAL (struct inode*) ; 
 int jbd2_journal_begin_ordered_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_begin_ordered_truncate (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ext4_begin_ordered_truncate(struct inode *inode,
					      loff_t new_size)
{
	trace_ext4_begin_ordered_truncate(inode, new_size);
	/*
	 * If jinode is zero, then we never opened the file for
	 * writing, so there's no need to call
	 * jbd2_journal_begin_ordered_truncate() since there's no
	 * outstanding writes we need to flush.
	 */
	if (!EXT4_I(inode)->jinode)
		return 0;
	return jbd2_journal_begin_ordered_truncate(EXT4_JOURNAL(inode),
						   EXT4_I(inode)->jinode,
						   new_size);
}