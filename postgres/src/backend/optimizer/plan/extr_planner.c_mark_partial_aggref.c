#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ aggtranstype; scalar_t__ aggsplit; scalar_t__ aggtype; } ;
typedef  TYPE_1__ Aggref ;
typedef  scalar_t__ AggSplit ;

/* Variables and functions */
 scalar_t__ AGGSPLIT_SIMPLE ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BYTEAOID ; 
 scalar_t__ DO_AGGSPLIT_SERIALIZE (scalar_t__) ; 
 scalar_t__ DO_AGGSPLIT_SKIPFINAL (scalar_t__) ; 
 scalar_t__ INTERNALOID ; 
 int OidIsValid (scalar_t__) ; 

void
mark_partial_aggref(Aggref *agg, AggSplit aggsplit)
{
	/* aggtranstype should be computed by this point */
	Assert(OidIsValid(agg->aggtranstype));
	/* ... but aggsplit should still be as the parser left it */
	Assert(agg->aggsplit == AGGSPLIT_SIMPLE);

	/* Mark the Aggref with the intended partial-aggregation mode */
	agg->aggsplit = aggsplit;

	/*
	 * Adjust result type if needed.  Normally, a partial aggregate returns
	 * the aggregate's transition type; but if that's INTERNAL and we're
	 * serializing, it returns BYTEA instead.
	 */
	if (DO_AGGSPLIT_SKIPFINAL(aggsplit))
	{
		if (agg->aggtranstype == INTERNALOID && DO_AGGSPLIT_SERIALIZE(aggsplit))
			agg->aggtype = BYTEAOID;
		else
			agg->aggtype = agg->aggtranstype;
	}
}