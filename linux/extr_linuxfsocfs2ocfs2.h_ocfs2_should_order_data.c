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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int s_mount_opt; } ;

/* Variables and functions */
 int OCFS2_MOUNT_DATA_WRITEBACK ; 
 TYPE_1__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_should_order_data(struct inode *inode)
{
	if (!S_ISREG(inode->i_mode))
		return 0;
	if (OCFS2_SB(inode->i_sb)->s_mount_opt & OCFS2_MOUNT_DATA_WRITEBACK)
		return 0;
	return 1;
}