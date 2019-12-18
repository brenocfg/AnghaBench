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
struct TYPE_3__ {int len; size_t* entries; int /*<<< orphan*/  isnull; int /*<<< orphan*/  attr; scalar_t__* dontcare; } ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GistSplitUnion ;
typedef  int /*<<< orphan*/  GISTSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  gistMakeUnionItVec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gistunionsubkeyvec(GISTSTATE *giststate, IndexTuple *itvec,
				   GistSplitUnion *gsvp)
{
	IndexTuple *cleanedItVec;
	int			i,
				cleanedLen = 0;

	cleanedItVec = (IndexTuple *) palloc(sizeof(IndexTuple) * gsvp->len);

	for (i = 0; i < gsvp->len; i++)
	{
		if (gsvp->dontcare && gsvp->dontcare[gsvp->entries[i]])
			continue;

		cleanedItVec[cleanedLen++] = itvec[gsvp->entries[i] - 1];
	}

	gistMakeUnionItVec(giststate, cleanedItVec, cleanedLen,
					   gsvp->attr, gsvp->isnull);

	pfree(cleanedItVec);
}