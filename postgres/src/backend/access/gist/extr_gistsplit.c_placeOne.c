#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* nonLeafTupdesc; } ;
struct TYPE_10__ {int /*<<< orphan*/  spl_nright; void** spl_right; int /*<<< orphan*/  spl_nleft; void** spl_left; } ;
struct TYPE_11__ {TYPE_2__ splitVector; int /*<<< orphan*/ * spl_risnull; int /*<<< orphan*/ * spl_rattr; int /*<<< orphan*/ * spl_lisnull; int /*<<< orphan*/ * spl_lattr; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_3__ GistSplitVector ;
typedef  TYPE_4__ GISTSTATE ;
typedef  int /*<<< orphan*/  GISTENTRY ;

/* Variables and functions */
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  gistDeCompressAtt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  gistentryinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 float gistpenalty (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
placeOne(Relation r, GISTSTATE *giststate, GistSplitVector *v,
		 IndexTuple itup, OffsetNumber off, int attno)
{
	GISTENTRY	identry[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	bool		toLeft = true;

	gistDeCompressAtt(giststate, r, itup, NULL, (OffsetNumber) 0,
					  identry, isnull);

	for (; attno < giststate->nonLeafTupdesc->natts; attno++)
	{
		float		lpenalty,
					rpenalty;
		GISTENTRY	entry;

		gistentryinit(entry, v->spl_lattr[attno], r, NULL, 0, false);
		lpenalty = gistpenalty(giststate, attno, &entry, v->spl_lisnull[attno],
							   identry + attno, isnull[attno]);
		gistentryinit(entry, v->spl_rattr[attno], r, NULL, 0, false);
		rpenalty = gistpenalty(giststate, attno, &entry, v->spl_risnull[attno],
							   identry + attno, isnull[attno]);

		if (lpenalty != rpenalty)
		{
			if (lpenalty > rpenalty)
				toLeft = false;
			break;
		}
	}

	if (toLeft)
		v->splitVector.spl_left[v->splitVector.spl_nleft++] = off;
	else
		v->splitVector.spl_right[v->splitVector.spl_nright++] = off;
}