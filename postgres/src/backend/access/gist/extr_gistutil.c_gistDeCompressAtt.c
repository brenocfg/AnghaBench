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
struct TYPE_4__ {int /*<<< orphan*/  leafTupdesc; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GISTSTATE ;
typedef  int /*<<< orphan*/  GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistdentryinit (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

void
gistDeCompressAtt(GISTSTATE *giststate, Relation r, IndexTuple tuple, Page p,
				  OffsetNumber o, GISTENTRY *attdata, bool *isnull)
{
	int			i;

	for (i = 0; i < IndexRelationGetNumberOfKeyAttributes(r); i++)
	{
		Datum		datum;

		datum = index_getattr(tuple, i + 1, giststate->leafTupdesc, &isnull[i]);
		gistdentryinit(giststate, i, &attdata[i],
					   datum, r, p, o,
					   false, isnull[i]);
	}
}