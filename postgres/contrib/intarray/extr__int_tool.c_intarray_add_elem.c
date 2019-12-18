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
typedef  int int32 ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ARRNELEMS (int /*<<< orphan*/ *) ; 
 int* ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECKARRVALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/ * new_intArrayType (int) ; 

ArrayType *
intarray_add_elem(ArrayType *a, int32 elem)
{
	ArrayType  *result;
	int32	   *r;
	int32		c;

	CHECKARRVALID(a);
	c = ARRNELEMS(a);
	result = new_intArrayType(c + 1);
	r = ARRPTR(result);
	if (c > 0)
		memcpy(r, ARRPTR(a), c * sizeof(int32));
	r[c] = elem;
	return result;
}