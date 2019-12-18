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
typedef  int /*<<< orphan*/  ltree_gist ;
typedef  int /*<<< orphan*/  lquery ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_DIMS (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_SUBSCRIPT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NEXTVAL (int /*<<< orphan*/ *) ; 
 scalar_t__ array_contains_nulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ gist_between (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gist_qe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
arrq_cons(ltree_gist *key, ArrayType *_query)
{
	lquery	   *query = (lquery *) ARR_DATA_PTR(_query);
	int			num = ArrayGetNItems(ARR_NDIM(_query), ARR_DIMS(_query));

	if (ARR_NDIM(_query) > 1)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
				 errmsg("array must be one-dimensional")));
	if (array_contains_nulls(_query))
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("array must not contain nulls")));

	while (num > 0)
	{
		if (gist_qe(key, query) && gist_between(key, query))
			return true;
		num--;
		query = NEXTVAL(query);
	}
	return false;
}