#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t fclass; int /*<<< orphan*/  nextspan; int /*<<< orphan*/  pool; int /*<<< orphan*/  prevspan; } ;
typedef  TYPE_1__ dsa_area_span ;
struct TYPE_5__ {int /*<<< orphan*/ * spans; } ;
typedef  TYPE_2__ dsa_area_pool ;
typedef  int /*<<< orphan*/  dsa_area ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 void* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unlink_span(dsa_area *area, dsa_area_span *span)
{
	if (DsaPointerIsValid(span->nextspan))
	{
		dsa_area_span *next = dsa_get_address(area, span->nextspan);

		next->prevspan = span->prevspan;
	}
	if (DsaPointerIsValid(span->prevspan))
	{
		dsa_area_span *prev = dsa_get_address(area, span->prevspan);

		prev->nextspan = span->nextspan;
	}
	else
	{
		dsa_area_pool *pool = dsa_get_address(area, span->pool);

		pool->spans[span->fclass] = span->nextspan;
	}
}