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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dirty_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_DATA ; 
 int /*<<< orphan*/  F2FS_DIRTY_DENTS ; 
 int /*<<< orphan*/  F2FS_DIRTY_QDATA ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void inode_inc_dirty_pages(struct inode *inode)
{
	atomic_inc(&F2FS_I(inode)->dirty_pages);
	inc_page_count(F2FS_I_SB(inode), S_ISDIR(inode->i_mode) ?
				F2FS_DIRTY_DENTS : F2FS_DIRTY_DATA);
	if (IS_NOQUOTA(inode))
		inc_page_count(F2FS_I_SB(inode), F2FS_DIRTY_QDATA);
}