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
struct xfs_ifork {TYPE_1__ if_u1; int /*<<< orphan*/  if_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_iext_free_last_leaf(
	struct xfs_ifork	*ifp)
{
	ifp->if_height--;
	kmem_free(ifp->if_u1.if_root);
	ifp->if_u1.if_root = NULL;
}