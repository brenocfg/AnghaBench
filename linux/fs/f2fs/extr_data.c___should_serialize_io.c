#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {scalar_t__ cp_task; } ;
struct TYPE_3__ {scalar_t__ min_seq_blocks; } ;

/* Variables and functions */
 TYPE_2__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 TYPE_1__* SM_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 

__attribute__((used)) static inline bool __should_serialize_io(struct inode *inode,
					struct writeback_control *wbc)
{
	if (!S_ISREG(inode->i_mode))
		return false;
	if (IS_NOQUOTA(inode))
		return false;
	/* to avoid deadlock in path of data flush */
	if (F2FS_I(inode)->cp_task)
		return false;
	if (wbc->sync_mode != WB_SYNC_ALL)
		return true;
	if (get_dirty_pages(inode) >= SM_I(F2FS_I_SB(inode))->min_seq_blocks)
		return true;
	return false;
}