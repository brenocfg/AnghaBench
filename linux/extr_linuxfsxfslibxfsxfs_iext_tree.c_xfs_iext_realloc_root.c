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
struct TYPE_2__ {void* if_root; } ;
struct xfs_ifork {size_t if_bytes; TYPE_1__ if_u1; } ;
struct xfs_iext_rec {int dummy; } ;
struct xfs_iext_cursor {void* leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 size_t NODE_SIZE ; 
 size_t RECS_PER_LEAF ; 
 void* kmem_realloc (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xfs_iext_realloc_root(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur)
{
	size_t new_size = ifp->if_bytes + sizeof(struct xfs_iext_rec);
	void *new;

	/* account for the prev/next pointers */
	if (new_size / sizeof(struct xfs_iext_rec) == RECS_PER_LEAF)
		new_size = NODE_SIZE;

	new = kmem_realloc(ifp->if_u1.if_root, new_size, KM_NOFS);
	memset(new + ifp->if_bytes, 0, new_size - ifp->if_bytes);
	ifp->if_u1.if_root = new;
	cur->leaf = new;
}