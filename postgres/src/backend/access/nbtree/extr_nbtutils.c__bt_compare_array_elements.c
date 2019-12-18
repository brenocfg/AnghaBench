#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_2__ {scalar_t__ reverse; int /*<<< orphan*/  collation; int /*<<< orphan*/  flinfo; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ BTSortArrayContext ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVERT_COMPARE_RESULT (int) ; 

__attribute__((used)) static int
_bt_compare_array_elements(const void *a, const void *b, void *arg)
{
	Datum		da = *((const Datum *) a);
	Datum		db = *((const Datum *) b);
	BTSortArrayContext *cxt = (BTSortArrayContext *) arg;
	int32		compare;

	compare = DatumGetInt32(FunctionCall2Coll(&cxt->flinfo,
											  cxt->collation,
											  da, db));
	if (cxt->reverse)
		INVERT_COMPARE_RESULT(compare);
	return compare;
}