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
typedef  int int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/ * EOXactTupleDescArray ; 
 int EOXactTupleDescArrayLen ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int NextEOXactTupleDescNum ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
RememberToFreeTupleDescAtEOX(TupleDesc td)
{
	if (EOXactTupleDescArray == NULL)
	{
		MemoryContext oldcxt;

		oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

		EOXactTupleDescArray = (TupleDesc *) palloc(16 * sizeof(TupleDesc));
		EOXactTupleDescArrayLen = 16;
		NextEOXactTupleDescNum = 0;
		MemoryContextSwitchTo(oldcxt);
	}
	else if (NextEOXactTupleDescNum >= EOXactTupleDescArrayLen)
	{
		int32		newlen = EOXactTupleDescArrayLen * 2;

		Assert(EOXactTupleDescArrayLen > 0);

		EOXactTupleDescArray = (TupleDesc *) repalloc(EOXactTupleDescArray,
													  newlen * sizeof(TupleDesc));
		EOXactTupleDescArrayLen = newlen;
	}

	EOXactTupleDescArray[NextEOXactTupleDescNum++] = td;
}