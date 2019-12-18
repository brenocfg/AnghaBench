#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ domain_type; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_1__ DomainIOData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * CurrentMemoryContext ; 
 int /*<<< orphan*/  domain_check_input (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 TYPE_1__* domain_state_setup (scalar_t__,int,int /*<<< orphan*/ *) ; 

void
domain_check(Datum value, bool isnull, Oid domainType,
			 void **extra, MemoryContext mcxt)
{
	DomainIOData *my_extra = NULL;

	if (mcxt == NULL)
		mcxt = CurrentMemoryContext;

	/*
	 * We arrange to look up the needed info just once per series of calls,
	 * assuming the domain type doesn't change underneath us (which really
	 * shouldn't happen, but cope if it does).
	 */
	if (extra)
		my_extra = (DomainIOData *) *extra;
	if (my_extra == NULL || my_extra->domain_type != domainType)
	{
		my_extra = domain_state_setup(domainType, true, mcxt);
		if (extra)
			*extra = (void *) my_extra;
	}

	/*
	 * Do the necessary checks to ensure it's a valid domain value.
	 */
	domain_check_input(value, isnull, my_extra);
}