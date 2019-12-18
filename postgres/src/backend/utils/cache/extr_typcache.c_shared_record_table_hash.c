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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  dsa_area ;
typedef  scalar_t__ TupleDesc ;
struct TYPE_3__ {scalar_t__ local_tupdesc; int /*<<< orphan*/  shared_tupdesc; } ;
struct TYPE_4__ {TYPE_1__ u; scalar_t__ shared; } ;
typedef  TYPE_2__ SharedRecordTableKey ;

/* Variables and functions */
 scalar_t__ dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashTupleDesc (scalar_t__) ; 

__attribute__((used)) static uint32
shared_record_table_hash(const void *a, size_t size, void *arg)
{
	dsa_area   *area = (dsa_area *) arg;
	SharedRecordTableKey *k = (SharedRecordTableKey *) a;
	TupleDesc	t;

	if (k->shared)
		t = (TupleDesc) dsa_get_address(area, k->u.shared_tupdesc);
	else
		t = k->u.local_tupdesc;

	return hashTupleDesc(t);
}