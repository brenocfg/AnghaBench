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
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {scalar_t__ min_seq_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 TYPE_1__* SM_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 

__attribute__((used)) static inline bool __should_serialize_io(struct inode *inode,
					struct writeback_control *wbc)
{
	if (!S_ISREG(inode->i_mode))
		return false;
	if (wbc->sync_mode != WB_SYNC_ALL)
		return true;
	if (get_dirty_pages(inode) >= SM_I(F2FS_I_SB(inode))->min_seq_blocks)
		return true;
	return false;
}