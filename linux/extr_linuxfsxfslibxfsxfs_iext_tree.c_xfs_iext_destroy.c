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
struct TYPE_2__ {int /*<<< orphan*/ * if_root; } ;
struct xfs_ifork {TYPE_1__ if_u1; scalar_t__ if_height; scalar_t__ if_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_iext_destroy_node (int /*<<< orphan*/ *,scalar_t__) ; 

void
xfs_iext_destroy(
	struct xfs_ifork	*ifp)
{
	xfs_iext_destroy_node(ifp->if_u1.if_root, ifp->if_height);

	ifp->if_bytes = 0;
	ifp->if_height = 0;
	ifp->if_u1.if_root = NULL;
}