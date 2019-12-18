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
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  xa_is_node (void*) ; 
 int /*<<< orphan*/  xa_to_node (void*) ; 
 int /*<<< orphan*/  xas ; 
 void* xas_descend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xas_get_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xas_start (int /*<<< orphan*/ *) ; 

bool xa_get_mark(struct xarray *xa, unsigned long index, xa_mark_t mark)
{
	XA_STATE(xas, xa, index);
	void *entry;

	rcu_read_lock();
	entry = xas_start(&xas);
	while (xas_get_mark(&xas, mark)) {
		if (!xa_is_node(entry))
			goto found;
		entry = xas_descend(&xas, xa_to_node(entry));
	}
	rcu_read_unlock();
	return false;
 found:
	rcu_read_unlock();
	return true;
}