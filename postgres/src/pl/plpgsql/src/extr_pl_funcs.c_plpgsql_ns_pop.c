#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ itemtype; struct TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ PLPGSQL_NSTYPE_LABEL ; 
 TYPE_1__* ns_top ; 

void
plpgsql_ns_pop(void)
{
	Assert(ns_top != NULL);
	while (ns_top->itemtype != PLPGSQL_NSTYPE_LABEL)
		ns_top = ns_top->prev;
	ns_top = ns_top->prev;
}