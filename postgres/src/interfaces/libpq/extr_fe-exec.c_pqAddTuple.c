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
struct TYPE_3__ {size_t ntups; size_t tupArrSize; int memorySize; int /*<<< orphan*/ ** tuples; } ;
typedef  TYPE_1__ PGresult ;
typedef  int /*<<< orphan*/  PGresAttValue ;

/* Variables and functions */
 int INT_MAX ; 
 int SIZE_MAX ; 
 char* libpq_gettext (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static bool
pqAddTuple(PGresult *res, PGresAttValue *tup, const char **errmsgp)
{
	if (res->ntups >= res->tupArrSize)
	{
		/*
		 * Try to grow the array.
		 *
		 * We can use realloc because shallow copying of the structure is
		 * okay. Note that the first time through, res->tuples is NULL. While
		 * ANSI says that realloc() should act like malloc() in that case,
		 * some old C libraries (like SunOS 4.1.x) coredump instead. On
		 * failure realloc is supposed to return NULL without damaging the
		 * existing allocation. Note that the positions beyond res->ntups are
		 * garbage, not necessarily NULL.
		 */
		int			newSize;
		PGresAttValue **newTuples;

		/*
		 * Since we use integers for row numbers, we can't support more than
		 * INT_MAX rows.  Make sure we allow that many, though.
		 */
		if (res->tupArrSize <= INT_MAX / 2)
			newSize = (res->tupArrSize > 0) ? res->tupArrSize * 2 : 128;
		else if (res->tupArrSize < INT_MAX)
			newSize = INT_MAX;
		else
		{
			*errmsgp = libpq_gettext("PGresult cannot support more than INT_MAX tuples");
			return false;
		}

		/*
		 * Also, on 32-bit platforms we could, in theory, overflow size_t even
		 * before newSize gets to INT_MAX.  (In practice we'd doubtless hit
		 * OOM long before that, but let's check.)
		 */
#if INT_MAX >= (SIZE_MAX / 2)
		if (newSize > SIZE_MAX / sizeof(PGresAttValue *))
		{
			*errmsgp = libpq_gettext("size_t overflow");
			return false;
		}
#endif

		if (res->tuples == NULL)
			newTuples = (PGresAttValue **)
				malloc(newSize * sizeof(PGresAttValue *));
		else
			newTuples = (PGresAttValue **)
				realloc(res->tuples, newSize * sizeof(PGresAttValue *));
		if (!newTuples)
			return false;		/* malloc or realloc failed */
		res->memorySize +=
			(newSize - res->tupArrSize) * sizeof(PGresAttValue *);
		res->tupArrSize = newSize;
		res->tuples = newTuples;
	}
	res->tuples[res->ntups] = tup;
	res->ntups++;
	return true;
}