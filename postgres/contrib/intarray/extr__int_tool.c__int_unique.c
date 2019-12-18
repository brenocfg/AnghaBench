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
 int /*<<< orphan*/  ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isort_cmp ; 
 int qunique_arg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * resize_intArrayType (int /*<<< orphan*/ *,int) ; 

ArrayType *
_int_unique(ArrayType *r)
{
	int			num = ARRNELEMS(r);
	bool		duplicates_found;	/* not used */

	num = qunique_arg(ARRPTR(r), num, sizeof(int), isort_cmp,
					  &duplicates_found);

	return resize_intArrayType(r, num);
}