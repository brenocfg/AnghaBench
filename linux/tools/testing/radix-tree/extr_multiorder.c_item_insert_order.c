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
struct item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XA_STATE_ORDER (int /*<<< orphan*/ ,struct xarray*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  free (struct item*) ; 
 struct item* item_create (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  xas ; 
 int xas_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_nomem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,struct item*) ; 
 int /*<<< orphan*/  xas_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int item_insert_order(struct xarray *xa, unsigned long index,
			unsigned order)
{
	XA_STATE_ORDER(xas, xa, index, order);
	struct item *item = item_create(index, order);

	do {
		xas_lock(&xas);
		xas_store(&xas, item);
		xas_unlock(&xas);
	} while (xas_nomem(&xas, GFP_KERNEL));

	if (!xas_error(&xas))
		return 0;

	free(item);
	return xas_error(&xas);
}