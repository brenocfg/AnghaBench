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
struct TYPE_2__ {int /*<<< orphan*/  jinode; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ ext4_handle_valid (int /*<<< orphan*/ *) ; 
 int jbd2_journal_inode_ranged_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ext4_jbd2_inode_add_wait(handle_t *handle,
		struct inode *inode, loff_t start_byte, loff_t length)
{
	if (ext4_handle_valid(handle))
		return jbd2_journal_inode_ranged_wait(handle,
				EXT4_I(inode)->jinode, start_byte, length);
	return 0;
}