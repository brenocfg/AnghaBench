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
struct xa_state {scalar_t__ xa_node; TYPE_2__* xa_alloc; TYPE_1__* xa; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int /*<<< orphan*/  private_list; } ;
struct TYPE_4__ {int xa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ XAS_RESTART ; 
 scalar_t__ XA_ERROR (int /*<<< orphan*/ ) ; 
 int XA_FLAGS_ACCOUNT ; 
 int /*<<< orphan*/  XA_NODE_BUG_ON (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __GFP_ACCOUNT ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_node_cachep ; 
 int /*<<< orphan*/  xas_destroy (struct xa_state*) ; 

bool xas_nomem(struct xa_state *xas, gfp_t gfp)
{
	if (xas->xa_node != XA_ERROR(-ENOMEM)) {
		xas_destroy(xas);
		return false;
	}
	if (xas->xa->xa_flags & XA_FLAGS_ACCOUNT)
		gfp |= __GFP_ACCOUNT;
	xas->xa_alloc = kmem_cache_alloc(radix_tree_node_cachep, gfp);
	if (!xas->xa_alloc)
		return false;
	XA_NODE_BUG_ON(xas->xa_alloc, !list_empty(&xas->xa_alloc->private_list));
	xas->xa_node = XAS_RESTART;
	return true;
}