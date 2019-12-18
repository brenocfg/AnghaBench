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
 scalar_t__ ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECKARRVALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ * new_intArrayType (int) ; 

ArrayType *
intarray_concat_arrays(ArrayType *a, ArrayType *b)
{
	ArrayType  *result;
	int32		ac = ARRNELEMS(a);
	int32		bc = ARRNELEMS(b);

	CHECKARRVALID(a);
	CHECKARRVALID(b);
	result = new_intArrayType(ac + bc);
	if (ac)
		memcpy(ARRPTR(result), ARRPTR(a), ac * sizeof(int32));
	if (bc)
		memcpy(ARRPTR(result) + ac, ARRPTR(b), bc * sizeof(int32));
	return result;
}