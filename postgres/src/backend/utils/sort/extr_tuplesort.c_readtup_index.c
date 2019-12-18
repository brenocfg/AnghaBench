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
struct TYPE_6__ {int /*<<< orphan*/  indexRel; int /*<<< orphan*/  tapeset; scalar_t__ randomAccess; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_7__ {int /*<<< orphan*/  isnull1; int /*<<< orphan*/  datum1; void* tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  unsigned int* IndexTuple ;

/* Variables and functions */
 int /*<<< orphan*/  LogicalTapeReadExact (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getattr (unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readtup_alloc (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void
readtup_index(Tuplesortstate *state, SortTuple *stup,
			  int tapenum, unsigned int len)
{
	unsigned int tuplen = len - sizeof(unsigned int);
	IndexTuple	tuple = (IndexTuple) readtup_alloc(state, tuplen);

	LogicalTapeReadExact(state->tapeset, tapenum,
						 tuple, tuplen);
	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeReadExact(state->tapeset, tapenum,
							 &tuplen, sizeof(tuplen));
	stup->tuple = (void *) tuple;
	/* set up first-column key value */
	stup->datum1 = index_getattr(tuple,
								 1,
								 RelationGetDescr(state->indexRel),
								 &stup->isnull1);
}