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
typedef  int int32 ;
typedef  int float4 ;
struct TYPE_3__ {scalar_t__ type; int val; int /*<<< orphan*/  left; } ;
typedef  int Selectivity ;
typedef  TYPE_1__ ITEM ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP_PROBABILITY (int) ; 
 int /*<<< orphan*/  DEFAULT_EQ_SEL ; 
 int /*<<< orphan*/  ERROR ; 
 int Min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OPR ; 
 scalar_t__ VAL ; 
 scalar_t__ bsearch (int*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  compare_val_int4 ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static Selectivity
int_query_opr_selec(ITEM *item, Datum *mcelems, float4 *mcefreqs,
					int nmcelems, float4 minfreq)
{
	Selectivity selec;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	if (item->type == VAL)
	{
		Datum	   *searchres;

		if (mcelems == NULL)
			return (Selectivity) DEFAULT_EQ_SEL;

		searchres = (Datum *) bsearch(&item->val, mcelems, nmcelems,
									  sizeof(Datum), compare_val_int4);
		if (searchres)
		{
			/*
			 * The element is in MCELEM.  Return precise selectivity (or at
			 * least as precise as ANALYZE could find out).
			 */
			selec = mcefreqs[searchres - mcelems];
		}
		else
		{
			/*
			 * The element is not in MCELEM.  Punt, but assume that the
			 * selectivity cannot be more than minfreq / 2.
			 */
			selec = Min(DEFAULT_EQ_SEL, minfreq / 2);
		}
	}
	else if (item->type == OPR)
	{
		/* Current query node is an operator */
		Selectivity s1,
					s2;

		s1 = int_query_opr_selec(item - 1, mcelems, mcefreqs, nmcelems,
								 minfreq);
		switch (item->val)
		{
			case (int32) '!':
				selec = 1.0 - s1;
				break;

			case (int32) '&':
				s2 = int_query_opr_selec(item + item->left, mcelems, mcefreqs,
										 nmcelems, minfreq);
				selec = s1 * s2;
				break;

			case (int32) '|':
				s2 = int_query_opr_selec(item + item->left, mcelems, mcefreqs,
										 nmcelems, minfreq);
				selec = s1 + s2 - s1 * s2;
				break;

			default:
				elog(ERROR, "unrecognized operator: %d", item->val);
				selec = 0;		/* keep compiler quiet */
				break;
		}
	}
	else
	{
		elog(ERROR, "unrecognized int query item type: %u", item->type);
		selec = 0;				/* keep compiler quiet */
	}

	/* Clamp intermediate results to stay sane despite roundoff error */
	CLAMP_PROBABILITY(selec);

	return selec;
}