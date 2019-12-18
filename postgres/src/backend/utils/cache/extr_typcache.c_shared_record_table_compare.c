#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_area ;
typedef  scalar_t__ TupleDesc ;
struct TYPE_3__ {scalar_t__ local_tupdesc; int /*<<< orphan*/  shared_tupdesc; } ;
struct TYPE_4__ {TYPE_1__ u; scalar_t__ shared; } ;
typedef  TYPE_2__ SharedRecordTableKey ;

/* Variables and functions */
 scalar_t__ dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ equalTupleDescs (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
shared_record_table_compare(const void *a, const void *b, size_t size,
							void *arg)
{
	dsa_area   *area = (dsa_area *) arg;
	SharedRecordTableKey *k1 = (SharedRecordTableKey *) a;
	SharedRecordTableKey *k2 = (SharedRecordTableKey *) b;
	TupleDesc	t1;
	TupleDesc	t2;

	if (k1->shared)
		t1 = (TupleDesc) dsa_get_address(area, k1->u.shared_tupdesc);
	else
		t1 = k1->u.local_tupdesc;

	if (k2->shared)
		t2 = (TupleDesc) dsa_get_address(area, k2->u.shared_tupdesc);
	else
		t2 = k2->u.local_tupdesc;

	return equalTupleDescs(t1, t2) ? 0 : 1;
}