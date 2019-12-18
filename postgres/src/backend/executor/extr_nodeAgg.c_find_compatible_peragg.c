#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* peragg; } ;
struct TYPE_7__ {int /*<<< orphan*/  transno; scalar_t__ shareable; TYPE_1__* aggref; } ;
struct TYPE_6__ {scalar_t__ inputcollid; scalar_t__ aggtranstype; scalar_t__ aggstar; scalar_t__ aggvariadic; scalar_t__ aggkind; scalar_t__ aggfnoid; scalar_t__ aggtype; scalar_t__ aggcollid; int /*<<< orphan*/  aggdirectargs; int /*<<< orphan*/  aggfilter; int /*<<< orphan*/  aggdistinct; int /*<<< orphan*/  aggorder; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ Aggref ;
typedef  TYPE_2__* AggStatePerAgg ;
typedef  TYPE_3__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ contain_volatile_functions (int /*<<< orphan*/ *) ; 
 scalar_t__ equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
find_compatible_peragg(Aggref *newagg, AggState *aggstate,
					   int lastaggno, List **same_input_transnos)
{
	int			aggno;
	AggStatePerAgg peraggs;

	*same_input_transnos = NIL;

	/* we mustn't reuse the aggref if it contains volatile function calls */
	if (contain_volatile_functions((Node *) newagg))
		return -1;

	peraggs = aggstate->peragg;

	/*
	 * Search through the list of already seen aggregates. If we find an
	 * existing identical aggregate call, then we can re-use that one. While
	 * searching, we'll also collect a list of Aggrefs with the same input
	 * parameters. If no matching Aggref is found, the caller can potentially
	 * still re-use the transition state of one of them.  (At this stage we
	 * just compare the parsetrees; whether different aggregates share the
	 * same transition function will be checked later.)
	 */
	for (aggno = 0; aggno <= lastaggno; aggno++)
	{
		AggStatePerAgg peragg;
		Aggref	   *existingRef;

		peragg = &peraggs[aggno];
		existingRef = peragg->aggref;

		/* all of the following must be the same or it's no match */
		if (newagg->inputcollid != existingRef->inputcollid ||
			newagg->aggtranstype != existingRef->aggtranstype ||
			newagg->aggstar != existingRef->aggstar ||
			newagg->aggvariadic != existingRef->aggvariadic ||
			newagg->aggkind != existingRef->aggkind ||
			!equal(newagg->args, existingRef->args) ||
			!equal(newagg->aggorder, existingRef->aggorder) ||
			!equal(newagg->aggdistinct, existingRef->aggdistinct) ||
			!equal(newagg->aggfilter, existingRef->aggfilter))
			continue;

		/* if it's the same aggregate function then report exact match */
		if (newagg->aggfnoid == existingRef->aggfnoid &&
			newagg->aggtype == existingRef->aggtype &&
			newagg->aggcollid == existingRef->aggcollid &&
			equal(newagg->aggdirectargs, existingRef->aggdirectargs))
		{
			list_free(*same_input_transnos);
			*same_input_transnos = NIL;
			return aggno;
		}

		/*
		 * Not identical, but it had the same inputs.  If the final function
		 * permits sharing, return its transno to the caller, in case we can
		 * re-use its per-trans state.  (If there's already sharing going on,
		 * we might report a transno more than once.  find_compatible_pertrans
		 * is cheap enough that it's not worth spending cycles to avoid that.)
		 */
		if (peragg->shareable)
			*same_input_transnos = lappend_int(*same_input_transnos,
											   peragg->transno);
	}

	return -1;
}