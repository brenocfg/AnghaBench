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
typedef  scalar_t__ xfs_fsize_t ;
struct TYPE_2__ {scalar_t__ di_size; } ;
struct xfs_inode {TYPE_1__ i_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_fsize_t
xfs_new_eof(struct xfs_inode *ip, xfs_fsize_t new_size)
{
	xfs_fsize_t i_size = i_size_read(VFS_I(ip));

	if (new_size > i_size || new_size < 0)
		new_size = i_size;
	return new_size > ip->i_d.di_size ? new_size : 0;
}