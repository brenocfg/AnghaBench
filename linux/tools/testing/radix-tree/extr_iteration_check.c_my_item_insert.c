#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xarray {int dummy; } ;
struct item {int order; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,struct xarray*,unsigned long) ; 
 int /*<<< orphan*/  free (struct item*) ; 
 struct item* item_create (unsigned long,int /*<<< orphan*/ ) ; 
 int max_order ; 
 int /*<<< orphan*/  xas ; 
 scalar_t__ xas_find_conflict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_nomem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_set_order (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,struct item*) ; 
 int /*<<< orphan*/  xas_unlock (int /*<<< orphan*/ *) ; 

void my_item_insert(struct xarray *xa, unsigned long index)
{
	XA_STATE(xas, xa, index);
	struct item *item = item_create(index, 0);
	int order;

retry:
	xas_lock(&xas);
	for (order = max_order; order >= 0; order--) {
		xas_set_order(&xas, index, order);
		item->order = order;
		if (xas_find_conflict(&xas))
			continue;
		xas_store(&xas, item);
		xas_set_mark(&xas, TAG);
		break;
	}
	xas_unlock(&xas);
	if (xas_nomem(&xas, GFP_KERNEL))
		goto retry;
	if (order < 0)
		free(item);
}