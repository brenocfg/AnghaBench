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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ARRNELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * new_intArrayType (int) ; 

ArrayType *
copy_intArrayType(ArrayType *a)
{
	ArrayType  *r;
	int			n = ARRNELEMS(a);

	r = new_intArrayType(n);
	memcpy(ARRPTR(r), ARRPTR(a), n * sizeof(int32));
	return r;
}