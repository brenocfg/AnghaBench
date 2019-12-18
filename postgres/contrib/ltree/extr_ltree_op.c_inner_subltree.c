#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ltree_level ;
struct TYPE_6__ {int numlevel; } ;
typedef  TYPE_1__ ltree ;
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * LEVEL_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LTREE_FIRST (TYPE_1__*) ; 
 scalar_t__ LTREE_HDRSIZE ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ palloc0 (scalar_t__) ; 

__attribute__((used)) static ltree *
inner_subltree(ltree *t, int32 startpos, int32 endpos)
{
	char	   *start = NULL,
			   *end = NULL;
	ltree_level *ptr = LTREE_FIRST(t);
	ltree	   *res;
	int			i;

	if (startpos < 0 || endpos < 0 || startpos >= t->numlevel || startpos > endpos)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid positions")));

	if (endpos > t->numlevel)
		endpos = t->numlevel;

	start = end = (char *) ptr;
	for (i = 0; i < endpos; i++)
	{
		if (i == startpos)
			start = (char *) ptr;
		if (i == endpos - 1)
		{
			end = (char *) LEVEL_NEXT(ptr);
			break;
		}
		ptr = LEVEL_NEXT(ptr);
	}

	res = (ltree *) palloc0(LTREE_HDRSIZE + (end - start));
	SET_VARSIZE(res, LTREE_HDRSIZE + (end - start));
	res->numlevel = endpos - startpos;

	memcpy(LTREE_FIRST(res), start, end - start);

	return res;
}