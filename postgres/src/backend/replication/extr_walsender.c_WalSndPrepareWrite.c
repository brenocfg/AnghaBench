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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WalSndPrepareWrite(LogicalDecodingContext *ctx, XLogRecPtr lsn, TransactionId xid, bool last_write)
{
	/* can't have sync rep confused by sending the same LSN several times */
	if (!last_write)
		lsn = InvalidXLogRecPtr;

	resetStringInfo(ctx->out);

	pq_sendbyte(ctx->out, 'w');
	pq_sendint64(ctx->out, lsn);	/* dataStart */
	pq_sendint64(ctx->out, lsn);	/* walEnd */

	/*
	 * Fill out the sendtime later, just as it's done in XLogSendPhysical, but
	 * reserve space here.
	 */
	pq_sendint64(ctx->out, 0);	/* sendtime */
}