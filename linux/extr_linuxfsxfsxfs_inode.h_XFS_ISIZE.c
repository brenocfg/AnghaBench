#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_fsize_t ;
struct TYPE_4__ {int /*<<< orphan*/  di_size; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_2__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  i_size_read (TYPE_2__*) ; 

__attribute__((used)) static inline xfs_fsize_t XFS_ISIZE(struct xfs_inode *ip)
{
	if (S_ISREG(VFS_I(ip)->i_mode))
		return i_size_read(VFS_I(ip));
	return ip->i_d.di_size;
}