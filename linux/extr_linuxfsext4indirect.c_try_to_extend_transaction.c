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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ EXT4_RESERVE_TRANS_BLOCKS ; 
 int /*<<< orphan*/  ext4_blocks_for_truncate (struct inode*) ; 
 scalar_t__ ext4_handle_has_enough_credits (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ext4_handle_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_journal_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_to_extend_transaction(handle_t *handle, struct inode *inode)
{
	if (!ext4_handle_valid(handle))
		return 0;
	if (ext4_handle_has_enough_credits(handle, EXT4_RESERVE_TRANS_BLOCKS+1))
		return 0;
	if (!ext4_journal_extend(handle, ext4_blocks_for_truncate(inode)))
		return 0;
	return 1;
}