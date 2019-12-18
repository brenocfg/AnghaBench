#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  datum_context; } ;
struct TYPE_5__ {scalar_t__ dtype; int /*<<< orphan*/ * erh; } ;
typedef  TYPE_1__ PLpgSQL_rec ;
typedef  TYPE_2__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DeleteExpandedObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExpandedRecordGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PLPGSQL_DTYPE_REC ; 
 int /*<<< orphan*/  TransferExpandedRecord (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assign_record_var(PLpgSQL_execstate *estate, PLpgSQL_rec *rec,
				  ExpandedRecordHeader *erh)
{
	Assert(rec->dtype == PLPGSQL_DTYPE_REC);

	/* Transfer new record object into datum_context */
	TransferExpandedRecord(erh, estate->datum_context);

	/* Free the old value ... */
	if (rec->erh)
		DeleteExpandedObject(ExpandedRecordGetDatum(rec->erh));

	/* ... and install the new */
	rec->erh = erh;
}