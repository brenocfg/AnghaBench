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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetAttributeByName (int /*<<< orphan*/ ,char*,int*) ; 

bool
c_overpaid(HeapTupleHeader t,	/* the current instance of EMP */
		   int32 limit)
{
	bool		isnull;
	int32		salary;

	salary = DatumGetInt32(GetAttributeByName(t, "salary", &isnull));
	if (isnull)
		return false;
	return salary > limit;
}