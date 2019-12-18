#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ltree_level ;
struct TYPE_13__ {int numlevel; } ;
typedef  TYPE_2__ ltree ;

/* Variables and functions */
 scalar_t__ LEVEL_HDRSIZE ; 
 TYPE_1__* LEVEL_NEXT (TYPE_1__*) ; 
 TYPE_1__* LTREE_FIRST (TYPE_2__*) ; 
 int LTREE_HDRSIZE ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_2__*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ palloc0 (int) ; 

ltree *
lca_inner(ltree **a, int len)
{
	int			tmp,
				num,
				i,
				reslen;
	ltree	  **ptr;
	ltree_level *l1,
			   *l2;
	ltree	   *res;

	if (len <= 0)
		return NULL;			/* no inputs? */
	if ((*a)->numlevel == 0)
		return NULL;			/* any empty input means NULL result */

	/* num is the length of the longest common ancestor so far */
	num = (*a)->numlevel - 1;

	/* Compare each additional input to *a */
	ptr = a + 1;
	while (ptr - a < len)
	{
		if ((*ptr)->numlevel == 0)
			return NULL;
		else if ((*ptr)->numlevel == 1)
			num = 0;
		else
		{
			l1 = LTREE_FIRST(*a);
			l2 = LTREE_FIRST(*ptr);
			tmp = Min(num, (*ptr)->numlevel - 1);
			num = 0;
			for (i = 0; i < tmp; i++)
			{
				if (l1->len == l2->len &&
					memcmp(l1->name, l2->name, l1->len) == 0)
					num = i + 1;
				else
					break;
				l1 = LEVEL_NEXT(l1);
				l2 = LEVEL_NEXT(l2);
			}
		}
		ptr++;
	}

	/* Now compute size of result ... */
	reslen = LTREE_HDRSIZE;
	l1 = LTREE_FIRST(*a);
	for (i = 0; i < num; i++)
	{
		reslen += MAXALIGN(l1->len + LEVEL_HDRSIZE);
		l1 = LEVEL_NEXT(l1);
	}

	/* ... and construct it by copying from *a */
	res = (ltree *) palloc0(reslen);
	SET_VARSIZE(res, reslen);
	res->numlevel = num;

	l1 = LTREE_FIRST(*a);
	l2 = LTREE_FIRST(res);

	for (i = 0; i < num; i++)
	{
		memcpy(l2, l1, MAXALIGN(l1->len + LEVEL_HDRSIZE));
		l1 = LEVEL_NEXT(l1);
		l2 = LEVEL_NEXT(l2);
	}

	return res;
}