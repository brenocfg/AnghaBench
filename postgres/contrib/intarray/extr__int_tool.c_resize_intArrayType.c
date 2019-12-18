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
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ARRNELEMS (int /*<<< orphan*/ *) ; 
 int ARR_DATA_OFFSET (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * construct_empty_array (int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

ArrayType *
resize_intArrayType(ArrayType *a, int num)
{
	int			nbytes;
	int			i;

	/* if no elements, return a zero-dimensional array */
	if (num <= 0)
	{
		Assert(num == 0);
		a = construct_empty_array(INT4OID);
		return a;
	}

	if (num == ARRNELEMS(a))
		return a;

	nbytes = ARR_DATA_OFFSET(a) + sizeof(int) * num;

	a = (ArrayType *) repalloc(a, nbytes);

	SET_VARSIZE(a, nbytes);
	/* usually the array should be 1-D already, but just in case ... */
	for (i = 0; i < ARR_NDIM(a); i++)
	{
		ARR_DIMS(a)[i] = num;
		num = 1;
	}
	return a;
}