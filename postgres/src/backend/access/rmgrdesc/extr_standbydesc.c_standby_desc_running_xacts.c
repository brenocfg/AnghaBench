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
struct TYPE_3__ {int xcnt; int* xids; scalar_t__ subxid_overflow; int /*<<< orphan*/  oldestRunningXid; int /*<<< orphan*/  latestCompletedXid; int /*<<< orphan*/  nextXid; } ;
typedef  TYPE_1__ xl_running_xacts ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
standby_desc_running_xacts(StringInfo buf, xl_running_xacts *xlrec)
{
	int			i;

	appendStringInfo(buf, "nextXid %u latestCompletedXid %u oldestRunningXid %u",
					 xlrec->nextXid,
					 xlrec->latestCompletedXid,
					 xlrec->oldestRunningXid);
	if (xlrec->xcnt > 0)
	{
		appendStringInfo(buf, "; %d xacts:", xlrec->xcnt);
		for (i = 0; i < xlrec->xcnt; i++)
			appendStringInfo(buf, " %u", xlrec->xids[i]);
	}

	if (xlrec->subxid_overflow)
		appendStringInfoString(buf, "; subxid ovf");
}