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
typedef  char uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {int /*<<< orphan*/  commit_time; int /*<<< orphan*/  end_lsn; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ReorderBufferTXN ;

/* Variables and functions */
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
logicalrep_write_commit(StringInfo out, ReorderBufferTXN *txn,
						XLogRecPtr commit_lsn)
{
	uint8		flags = 0;

	pq_sendbyte(out, 'C');		/* sending COMMIT */

	/* send the flags field (unused for now) */
	pq_sendbyte(out, flags);

	/* send fields */
	pq_sendint64(out, commit_lsn);
	pq_sendint64(out, txn->end_lsn);
	pq_sendint64(out, txn->commit_time);
}