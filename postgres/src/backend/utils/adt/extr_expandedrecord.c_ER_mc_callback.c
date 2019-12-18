#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_5__ {TYPE_1__* er_tupdesc; } ;
struct TYPE_4__ {scalar_t__ tdrefcount; } ;
typedef  TYPE_2__ ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  FreeTupleDesc (TYPE_1__*) ; 

__attribute__((used)) static void
ER_mc_callback(void *arg)
{
	ExpandedRecordHeader *erh = (ExpandedRecordHeader *) arg;
	TupleDesc	tupdesc = erh->er_tupdesc;

	/* Release our privately-managed tupdesc refcount, if any */
	if (tupdesc)
	{
		erh->er_tupdesc = NULL; /* just for luck */
		if (tupdesc->tdrefcount > 0)
		{
			if (--tupdesc->tdrefcount == 0)
				FreeTupleDesc(tupdesc);
		}
	}
}