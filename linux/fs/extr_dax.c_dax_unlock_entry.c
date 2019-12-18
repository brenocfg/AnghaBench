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
struct xa_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int dax_is_locked (void*) ; 
 int /*<<< orphan*/  dax_wake_entry (struct xa_state*,void*,int) ; 
 int /*<<< orphan*/  xas_lock_irq (struct xa_state*) ; 
 int /*<<< orphan*/  xas_reset (struct xa_state*) ; 
 void* xas_store (struct xa_state*,void*) ; 
 int /*<<< orphan*/  xas_unlock_irq (struct xa_state*) ; 

__attribute__((used)) static void dax_unlock_entry(struct xa_state *xas, void *entry)
{
	void *old;

	BUG_ON(dax_is_locked(entry));
	xas_reset(xas);
	xas_lock_irq(xas);
	old = xas_store(xas, entry);
	xas_unlock_irq(xas);
	BUG_ON(!dax_is_locked(old));
	dax_wake_entry(xas, entry, false);
}