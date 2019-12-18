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
typedef  scalar_t__ IndexTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IndexTupleSize (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 scalar_t__* palloc (int) ; 

__attribute__((used)) static IndexTuple *
decodePageSplitRecord(char *begin, int len, int *n)
{
	char	   *ptr;
	int			i = 0;
	IndexTuple *tuples;

	/* extract the number of tuples */
	memcpy(n, begin, sizeof(int));
	ptr = begin + sizeof(int);

	tuples = palloc(*n * sizeof(IndexTuple));

	for (i = 0; i < *n; i++)
	{
		Assert(ptr - begin < len);
		tuples[i] = (IndexTuple) ptr;
		ptr += IndexTupleSize((IndexTuple) ptr);
	}
	Assert(ptr - begin == len);

	return tuples;
}