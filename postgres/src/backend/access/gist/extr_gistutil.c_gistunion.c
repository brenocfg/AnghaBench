#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  gistFormTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  gistMakeUnionItVec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 

IndexTuple
gistunion(Relation r, IndexTuple *itvec, int len, GISTSTATE *giststate)
{
	Datum		attr[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];

	gistMakeUnionItVec(giststate, itvec, len, attr, isnull);

	return gistFormTuple(giststate, r, attr, isnull, false);
}