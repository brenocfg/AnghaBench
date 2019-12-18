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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE_ORDER (int /*<<< orphan*/ ,struct xarray*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  xas ; 
 int /*<<< orphan*/  xas_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_nomem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xas_store (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  xas_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *xa_store_order(struct xarray *xa, unsigned long index,
		unsigned order, void *entry, gfp_t gfp)
{
	XA_STATE_ORDER(xas, xa, index, order);
	void *curr;

	do {
		xas_lock(&xas);
		curr = xas_store(&xas, entry);
		xas_unlock(&xas);
	} while (xas_nomem(&xas, gfp));

	return curr;
}