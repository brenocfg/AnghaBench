#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xarray {int /*<<< orphan*/  xa_head; } ;
struct TYPE_7__ {int /*<<< orphan*/ * xa_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XA_FREE_MARK ; 
 int /*<<< orphan*/  XA_STATE (TYPE_1__,struct xarray*,int /*<<< orphan*/ ) ; 
 void* xa_head_locked (struct xarray*) ; 
 scalar_t__ xa_is_node (void*) ; 
 int /*<<< orphan*/  xa_mark_clear (struct xarray*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_to_node (void*) ; 
 scalar_t__ xa_zero_busy (struct xarray*) ; 
 TYPE_1__ xas ; 
 int /*<<< orphan*/  xas_free_nodes (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_init_marks (TYPE_1__*) ; 
 int /*<<< orphan*/  xas_lock_irqsave (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  xas_unlock_irqrestore (TYPE_1__*,unsigned long) ; 

void xa_destroy(struct xarray *xa)
{
	XA_STATE(xas, xa, 0);
	unsigned long flags;
	void *entry;

	xas.xa_node = NULL;
	xas_lock_irqsave(&xas, flags);
	entry = xa_head_locked(xa);
	RCU_INIT_POINTER(xa->xa_head, NULL);
	xas_init_marks(&xas);
	if (xa_zero_busy(xa))
		xa_mark_clear(xa, XA_FREE_MARK);
	/* lockdep checks we're still holding the lock in xas_free_nodes() */
	if (xa_is_node(entry))
		xas_free_nodes(&xas, xa_to_node(entry));
	xas_unlock_irqrestore(&xas, flags);
}