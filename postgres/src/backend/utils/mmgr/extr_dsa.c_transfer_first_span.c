#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* dsa_pointer ;
struct TYPE_5__ {void* nextspan; int fclass; void* prevspan; } ;
typedef  TYPE_1__ dsa_area_span ;
struct TYPE_6__ {void** spans; } ;
typedef  TYPE_2__ dsa_area_pool ;
typedef  int /*<<< orphan*/  dsa_area ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (void*) ; 
 void* InvalidDsaPointer ; 
 TYPE_1__* dsa_get_address (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static bool
transfer_first_span(dsa_area *area,
					dsa_area_pool *pool, int fromclass, int toclass)
{
	dsa_pointer span_pointer;
	dsa_area_span *span;
	dsa_area_span *nextspan;

	/* Can't do it if source list is empty. */
	span_pointer = pool->spans[fromclass];
	if (!DsaPointerIsValid(span_pointer))
		return false;

	/* Remove span from head of source list. */
	span = dsa_get_address(area, span_pointer);
	pool->spans[fromclass] = span->nextspan;
	if (DsaPointerIsValid(span->nextspan))
	{
		nextspan = (dsa_area_span *)
			dsa_get_address(area, span->nextspan);
		nextspan->prevspan = InvalidDsaPointer;
	}

	/* Add span to head of target list. */
	span->nextspan = pool->spans[toclass];
	pool->spans[toclass] = span_pointer;
	if (DsaPointerIsValid(span->nextspan))
	{
		nextspan = (dsa_area_span *)
			dsa_get_address(area, span->nextspan);
		nextspan->prevspan = span_pointer;
	}
	span->fclass = toclass;

	return true;
}