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
 unsigned long DAX_LOCKED ; 
 int /*<<< orphan*/  xa_mk_value (unsigned long) ; 
 unsigned long xa_to_value (void*) ; 
 void* xas_store (struct xa_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dax_lock_entry(struct xa_state *xas, void *entry)
{
	unsigned long v = xa_to_value(entry);
	return xas_store(xas, xa_mk_value(v | DAX_LOCKED));
}