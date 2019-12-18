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
typedef  scalar_t__ uint8 ;
struct TYPE_3__ {void* committime; void* end_lsn; void* commit_lsn; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepCommitData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 void* pq_getmsgint64 (int /*<<< orphan*/ ) ; 

void
logicalrep_read_commit(StringInfo in, LogicalRepCommitData *commit_data)
{
	/* read flags (unused for now) */
	uint8		flags = pq_getmsgbyte(in);

	if (flags != 0)
		elog(ERROR, "unrecognized flags %u in commit message", flags);

	/* read fields */
	commit_data->commit_lsn = pq_getmsgint64(in);
	commit_data->end_lsn = pq_getmsgint64(in);
	commit_data->committime = pq_getmsgint64(in);
}