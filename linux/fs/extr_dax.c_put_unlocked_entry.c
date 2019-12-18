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
 int /*<<< orphan*/  dax_is_conflict (void*) ; 
 int /*<<< orphan*/  dax_wake_entry (struct xa_state*,void*,int) ; 

__attribute__((used)) static void put_unlocked_entry(struct xa_state *xas, void *entry)
{
	/* If we were the only waiter woken, wake the next one */
	if (entry && !dax_is_conflict(entry))
		dax_wake_entry(xas, entry, false);
}