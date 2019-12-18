#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuplen ;
struct TYPE_7__ {int /*<<< orphan*/  myfile; scalar_t__ backward; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_8__ {int t_len; } ;
typedef  TYPE_2__* MinimalTuple ;

/* Variables and functions */
 int BufFileWrite (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FREEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_2__*) ; 
 int MINIMAL_TUPLE_DATA_OFFSET ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_free_minimal_tuple (TYPE_2__*) ; 

__attribute__((used)) static void
writetup_heap(Tuplestorestate *state, void *tup)
{
	MinimalTuple tuple = (MinimalTuple) tup;

	/* the part of the MinimalTuple we'll write: */
	char	   *tupbody = (char *) tuple + MINIMAL_TUPLE_DATA_OFFSET;
	unsigned int tupbodylen = tuple->t_len - MINIMAL_TUPLE_DATA_OFFSET;

	/* total on-disk footprint: */
	unsigned int tuplen = tupbodylen + sizeof(int);

	if (BufFileWrite(state->myfile, (void *) &tuplen,
					 sizeof(tuplen)) != sizeof(tuplen))
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not write to tuplestore temporary file: %m")));
	if (BufFileWrite(state->myfile, (void *) tupbody,
					 tupbodylen) != (size_t) tupbodylen)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not write to tuplestore temporary file: %m")));
	if (state->backward)		/* need trailing length word? */
		if (BufFileWrite(state->myfile, (void *) &tuplen,
						 sizeof(tuplen)) != sizeof(tuplen))
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not write to tuplestore temporary file: %m")));

	FREEMEM(state, GetMemoryChunkSpace(tuple));
	heap_free_minimal_tuple(tuple);
}