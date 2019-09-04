#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__ s_ndevs; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LFS ; 
 int WRITE ; 
 scalar_t__ f2fs_post_read_required (struct inode*) ; 
 scalar_t__ test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_force_buffered_io(struct inode *inode, int rw)
{
	return (f2fs_post_read_required(inode) ||
			(rw == WRITE && test_opt(F2FS_I_SB(inode), LFS)) ||
			F2FS_I_SB(inode)->s_ndevs);
}