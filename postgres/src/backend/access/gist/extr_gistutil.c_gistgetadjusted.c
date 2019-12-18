#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  key; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_2__ GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int INDEX_MAX_KEYS ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistDeCompressAtt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 TYPE_1__* gistFormTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  gistKeyIsEQ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistMakeUnionKey (int /*<<< orphan*/ *,int,TYPE_2__*,int,TYPE_2__*,int,int /*<<< orphan*/ *,int*) ; 

IndexTuple
gistgetadjusted(Relation r, IndexTuple oldtup, IndexTuple addtup, GISTSTATE *giststate)
{
	bool		neednew = false;
	GISTENTRY	oldentries[INDEX_MAX_KEYS],
				addentries[INDEX_MAX_KEYS];
	bool		oldisnull[INDEX_MAX_KEYS],
				addisnull[INDEX_MAX_KEYS];
	Datum		attr[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	IndexTuple	newtup = NULL;
	int			i;

	gistDeCompressAtt(giststate, r, oldtup, NULL,
					  (OffsetNumber) 0, oldentries, oldisnull);

	gistDeCompressAtt(giststate, r, addtup, NULL,
					  (OffsetNumber) 0, addentries, addisnull);

	for (i = 0; i < IndexRelationGetNumberOfKeyAttributes(r); i++)
	{
		gistMakeUnionKey(giststate, i,
						 oldentries + i, oldisnull[i],
						 addentries + i, addisnull[i],
						 attr + i, isnull + i);

		if (neednew)
			/* we already need new key, so we can skip check */
			continue;

		if (isnull[i])
			/* union of key may be NULL if and only if both keys are NULL */
			continue;

		if (!addisnull[i])
		{
			if (oldisnull[i] ||
				!gistKeyIsEQ(giststate, i, oldentries[i].key, attr[i]))
				neednew = true;
		}
	}

	if (neednew)
	{
		/* need to update key */
		newtup = gistFormTuple(giststate, r, attr, isnull, false);
		newtup->t_tid = oldtup->t_tid;
	}

	return newtup;
}