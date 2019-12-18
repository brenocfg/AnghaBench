#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ er_magic; } ;
typedef  TYPE_1__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ ER_MAGIC ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_expanded_record_from_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ExpandedRecordHeader *
DatumGetExpandedRecord(Datum d)
{
	/* If it's a writable expanded record already, just return it */
	if (VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(d)))
	{
		ExpandedRecordHeader *erh = (ExpandedRecordHeader *) DatumGetEOHP(d);

		Assert(erh->er_magic == ER_MAGIC);
		return erh;
	}

	/* Else expand the hard way */
	d = make_expanded_record_from_datum(d, CurrentMemoryContext);
	return (ExpandedRecordHeader *) DatumGetEOHP(d);
}