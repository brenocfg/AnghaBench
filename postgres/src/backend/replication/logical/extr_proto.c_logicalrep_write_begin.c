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
struct TYPE_3__ {int /*<<< orphan*/  xid; int /*<<< orphan*/  commit_time; int /*<<< orphan*/  final_lsn; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ReorderBufferTXN ;

/* Variables and functions */
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
logicalrep_write_begin(StringInfo out, ReorderBufferTXN *txn)
{
	pq_sendbyte(out, 'B');		/* BEGIN */

	/* fixed fields */
	pq_sendint64(out, txn->final_lsn);
	pq_sendint64(out, txn->commit_time);
	pq_sendint32(out, txn->xid);
}