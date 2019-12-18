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
typedef  int int32 ;
struct TYPE_5__ {int keylen; int vallen; scalar_t__ isnull; int /*<<< orphan*/  val; int /*<<< orphan*/  key; scalar_t__ needfree; } ;
typedef  TYPE_1__ Pairs ;

/* Variables and functions */
 int /*<<< orphan*/  comparePairs ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 

int
hstoreUniquePairs(Pairs *a, int32 l, int32 *buflen)
{
	Pairs	   *ptr,
			   *res;

	*buflen = 0;
	if (l < 2)
	{
		if (l == 1)
			*buflen = a->keylen + ((a->isnull) ? 0 : a->vallen);
		return l;
	}

	qsort((void *) a, l, sizeof(Pairs), comparePairs);

	/*
	 * We can't use qunique here because we have some clean-up code to run on
	 * removed elements.
	 */
	ptr = a + 1;
	res = a;
	while (ptr - a < l)
	{
		if (ptr->keylen == res->keylen &&
			memcmp(ptr->key, res->key, res->keylen) == 0)
		{
			if (ptr->needfree)
			{
				pfree(ptr->key);
				pfree(ptr->val);
			}
		}
		else
		{
			*buflen += res->keylen + ((res->isnull) ? 0 : res->vallen);
			res++;
			if (res != ptr)
				memcpy(res, ptr, sizeof(Pairs));
		}

		ptr++;
	}

	*buflen += res->keylen + ((res->isnull) ? 0 : res->vallen);
	return res + 1 - a;
}