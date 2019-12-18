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
struct TYPE_3__ {scalar_t__ final_lsn; int /*<<< orphan*/  xid; void* committime; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepBeginData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 void* pq_getmsgint64 (int /*<<< orphan*/ ) ; 

void
logicalrep_read_begin(StringInfo in, LogicalRepBeginData *begin_data)
{
	/* read fields */
	begin_data->final_lsn = pq_getmsgint64(in);
	if (begin_data->final_lsn == InvalidXLogRecPtr)
		elog(ERROR, "final_lsn not set in begin message");
	begin_data->committime = pq_getmsgint64(in);
	begin_data->xid = pq_getmsgint(in, 4);
}