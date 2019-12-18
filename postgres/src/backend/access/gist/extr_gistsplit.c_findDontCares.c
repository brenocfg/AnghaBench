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
struct TYPE_4__ {int spl_nleft; int* spl_left; int spl_nright; int* spl_right; int /*<<< orphan*/  spl_ldatum; int /*<<< orphan*/  spl_rdatum; } ;
struct TYPE_5__ {int* spl_dontcare; TYPE_1__ splitVector; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_2__ GistSplitVector ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  int /*<<< orphan*/  GISTENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  gistentryinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 float gistpenalty (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
findDontCares(Relation r, GISTSTATE *giststate, GISTENTRY *valvec,
			  GistSplitVector *spl, int attno)
{
	int			i;
	GISTENTRY	entry;
	int			NumDontCare = 0;

	/*
	 * First, search the left-side tuples to see if any have zero penalty to
	 * be added to the right-side union key.
	 *
	 * attno column is known all-not-null (see gistSplitByKey), so we need not
	 * check for nulls
	 */
	gistentryinit(entry, spl->splitVector.spl_rdatum, r, NULL,
				  (OffsetNumber) 0, false);
	for (i = 0; i < spl->splitVector.spl_nleft; i++)
	{
		int			j = spl->splitVector.spl_left[i];
		float		penalty = gistpenalty(giststate, attno, &entry, false,
										  &valvec[j], false);

		if (penalty == 0.0)
		{
			spl->spl_dontcare[j] = true;
			NumDontCare++;
		}
	}

	/* And conversely for the right-side tuples */
	gistentryinit(entry, spl->splitVector.spl_ldatum, r, NULL,
				  (OffsetNumber) 0, false);
	for (i = 0; i < spl->splitVector.spl_nright; i++)
	{
		int			j = spl->splitVector.spl_right[i];
		float		penalty = gistpenalty(giststate, attno, &entry, false,
										  &valvec[j], false);

		if (penalty == 0.0)
		{
			spl->spl_dontcare[j] = true;
			NumDontCare++;
		}
	}

	return NumDontCare;
}