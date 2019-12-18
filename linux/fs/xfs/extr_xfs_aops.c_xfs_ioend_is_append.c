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
struct xfs_ioend {scalar_t__ io_offset; scalar_t__ io_size; int /*<<< orphan*/  io_inode; } ;
struct TYPE_3__ {scalar_t__ di_size; } ;
struct TYPE_4__ {TYPE_1__ i_d; } ;

/* Variables and functions */
 TYPE_2__* XFS_I (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xfs_ioend_is_append(struct xfs_ioend *ioend)
{
	return ioend->io_offset + ioend->io_size >
		XFS_I(ioend->io_inode)->i_d.di_size;
}