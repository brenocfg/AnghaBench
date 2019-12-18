#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuplen ;
struct TYPE_6__ {int /*<<< orphan*/  tapeset; scalar_t__ randomAccess; int /*<<< orphan*/  tuples; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_7__ {unsigned int datum1; int isnull1; int /*<<< orphan*/ * tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  unsigned int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LogicalTapeReadExact (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 unsigned int PointerGetDatum (void*) ; 
 void* readtup_alloc (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void
readtup_datum(Tuplesortstate *state, SortTuple *stup,
			  int tapenum, unsigned int len)
{
	unsigned int tuplen = len - sizeof(unsigned int);

	if (tuplen == 0)
	{
		/* it's NULL */
		stup->datum1 = (Datum) 0;
		stup->isnull1 = true;
		stup->tuple = NULL;
	}
	else if (!state->tuples)
	{
		Assert(tuplen == sizeof(Datum));
		LogicalTapeReadExact(state->tapeset, tapenum,
							 &stup->datum1, tuplen);
		stup->isnull1 = false;
		stup->tuple = NULL;
	}
	else
	{
		void	   *raddr = readtup_alloc(state, tuplen);

		LogicalTapeReadExact(state->tapeset, tapenum,
							 raddr, tuplen);
		stup->datum1 = PointerGetDatum(raddr);
		stup->isnull1 = false;
		stup->tuple = raddr;
	}

	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeReadExact(state->tapeset, tapenum,
							 &tuplen, sizeof(tuplen));
}