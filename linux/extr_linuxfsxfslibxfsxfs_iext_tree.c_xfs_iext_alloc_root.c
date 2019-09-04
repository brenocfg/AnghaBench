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
struct TYPE_2__ {int /*<<< orphan*/  if_root; } ;
struct xfs_ifork {scalar_t__ if_bytes; int if_height; TYPE_1__ if_u1; } ;
struct xfs_iext_rec {int dummy; } ;
struct xfs_iext_cursor {scalar_t__ pos; int /*<<< orphan*/  leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_iext_alloc_root(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur)
{
	ASSERT(ifp->if_bytes == 0);

	ifp->if_u1.if_root = kmem_zalloc(sizeof(struct xfs_iext_rec), KM_NOFS);
	ifp->if_height = 1;

	/* now that we have a node step into it */
	cur->leaf = ifp->if_u1.if_root;
	cur->pos = 0;
}