#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int isnull; scalar_t__ needfree; scalar_t__ vallen; int /*<<< orphan*/ * val; scalar_t__ keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Pairs ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int MaxAllocSize ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ ) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,int) ; 
 int hstoreUniquePairs (TYPE_1__*,int,int*) ; 
 TYPE_1__* palloc (int) ; 

Pairs *
hstoreArrayToPairs(ArrayType *a, int *npairs)
{
	Datum	   *key_datums;
	bool	   *key_nulls;
	int			key_count;
	Pairs	   *key_pairs;
	int			bufsiz;
	int			i,
				j;

	deconstruct_array(a,
					  TEXTOID, -1, false, 'i',
					  &key_datums, &key_nulls, &key_count);

	if (key_count == 0)
	{
		*npairs = 0;
		return NULL;
	}

	/*
	 * A text array uses at least eight bytes per element, so any overflow in
	 * "key_count * sizeof(Pairs)" is small enough for palloc() to catch.
	 * However, credible improvements to the array format could invalidate
	 * that assumption.  Therefore, use an explicit check rather than relying
	 * on palloc() to complain.
	 */
	if (key_count > MaxAllocSize / sizeof(Pairs))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("number of pairs (%d) exceeds the maximum allowed (%d)",
						key_count, (int) (MaxAllocSize / sizeof(Pairs)))));

	key_pairs = palloc(sizeof(Pairs) * key_count);

	for (i = 0, j = 0; i < key_count; i++)
	{
		if (!key_nulls[i])
		{
			key_pairs[j].key = VARDATA(key_datums[i]);
			key_pairs[j].keylen = VARSIZE(key_datums[i]) - VARHDRSZ;
			key_pairs[j].val = NULL;
			key_pairs[j].vallen = 0;
			key_pairs[j].needfree = 0;
			key_pairs[j].isnull = 1;
			j++;
		}
	}

	*npairs = hstoreUniquePairs(key_pairs, j, &bufsiz);

	return key_pairs;
}