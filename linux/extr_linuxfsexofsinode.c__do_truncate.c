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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; TYPE_1__* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  layout; } ;
struct exofs_i_info {int /*<<< orphan*/  oc; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct exofs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 scalar_t__ likely (int) ; 
 int ore_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

__attribute__((used)) static int _do_truncate(struct inode *inode, loff_t newsize)
{
	struct exofs_i_info *oi = exofs_i(inode);
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;
	int ret;

	inode->i_mtime = inode->i_ctime = current_time(inode);

	ret = ore_truncate(&sbi->layout, &oi->oc, (u64)newsize);
	if (likely(!ret))
		truncate_setsize(inode, newsize);

	EXOFS_DBGMSG2("(0x%lx) size=0x%llx ret=>%d\n",
		     inode->i_ino, newsize, ret);
	return ret;
}