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
struct TYPE_2__ {scalar_t__ max; scalar_t__ reserve; } ;
struct pts_fs_info {TYPE_1__ mount_opts; int /*<<< orphan*/  allocated_ptys; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pty_count ; 
 scalar_t__ pty_limit ; 
 scalar_t__ pty_reserve ; 

int devpts_new_index(struct pts_fs_info *fsi)
{
	int index = -ENOSPC;

	if (atomic_inc_return(&pty_count) >= (pty_limit -
			  (fsi->mount_opts.reserve ? 0 : pty_reserve)))
		goto out;

	index = ida_alloc_max(&fsi->allocated_ptys, fsi->mount_opts.max - 1,
			GFP_KERNEL);

out:
	if (index < 0)
		atomic_dec(&pty_count);
	return index;
}