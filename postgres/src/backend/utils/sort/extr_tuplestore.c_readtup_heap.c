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
struct TYPE_6__ {int /*<<< orphan*/  myfile; scalar_t__ backward; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_7__ {unsigned int t_len; } ;
typedef  TYPE_2__* MinimalTuple ;

/* Variables and functions */
 int BufFileRead (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_2__*) ; 
 unsigned int MINIMAL_TUPLE_DATA_OFFSET ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  palloc (unsigned int) ; 

__attribute__((used)) static void *
readtup_heap(Tuplestorestate *state, unsigned int len)
{
	unsigned int tupbodylen = len - sizeof(int);
	unsigned int tuplen = tupbodylen + MINIMAL_TUPLE_DATA_OFFSET;
	MinimalTuple tuple = (MinimalTuple) palloc(tuplen);
	char	   *tupbody = (char *) tuple + MINIMAL_TUPLE_DATA_OFFSET;

	USEMEM(state, GetMemoryChunkSpace(tuple));
	/* read in the tuple proper */
	tuple->t_len = tuplen;
	if (BufFileRead(state->myfile, (void *) tupbody,
					tupbodylen) != (size_t) tupbodylen)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read from tuplestore temporary file: %m")));
	if (state->backward)		/* need trailing length word? */
		if (BufFileRead(state->myfile, (void *) &tuplen,
						sizeof(tuplen)) != sizeof(tuplen))
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not read from tuplestore temporary file: %m")));
	return (void *) tuple;
}