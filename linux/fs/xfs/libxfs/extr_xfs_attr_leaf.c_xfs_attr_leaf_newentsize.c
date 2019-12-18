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
struct xfs_da_args {int /*<<< orphan*/  namelen; TYPE_1__* geo; int /*<<< orphan*/  valuelen; } ;
struct TYPE_2__ {int /*<<< orphan*/  blksize; } ;

/* Variables and functions */
 int xfs_attr_leaf_entsize_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_entsize_local_max (int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_entsize_remote (int /*<<< orphan*/ ) ; 

int
xfs_attr_leaf_newentsize(
	struct xfs_da_args	*args,
	int			*local)
{
	int			size;

	size = xfs_attr_leaf_entsize_local(args->namelen, args->valuelen);
	if (size < xfs_attr_leaf_entsize_local_max(args->geo->blksize)) {
		if (local)
			*local = 1;
		return size;
	}
	if (local)
		*local = 0;
	return xfs_attr_leaf_entsize_remote(args->namelen);
}