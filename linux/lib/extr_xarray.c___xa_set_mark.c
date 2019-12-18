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
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xarray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,struct xarray*,unsigned long) ; 
 int /*<<< orphan*/  xas ; 
 void* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __xa_set_mark(struct xarray *xa, unsigned long index, xa_mark_t mark)
{
	XA_STATE(xas, xa, index);
	void *entry = xas_load(&xas);

	if (entry)
		xas_set_mark(&xas, mark);
}