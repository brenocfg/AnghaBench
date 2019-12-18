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

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,struct xarray*,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ xa_is_zero (void*) ; 
 int /*<<< orphan*/  xas ; 
 void* xas_load (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_retry (int /*<<< orphan*/ *,void*) ; 

void *xa_load(struct xarray *xa, unsigned long index)
{
	XA_STATE(xas, xa, index);
	void *entry;

	rcu_read_lock();
	do {
		entry = xas_load(&xas);
		if (xa_is_zero(entry))
			entry = NULL;
	} while (xas_retry(&xas, entry));
	rcu_read_unlock();

	return entry;
}