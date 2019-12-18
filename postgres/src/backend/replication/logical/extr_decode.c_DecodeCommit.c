#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int xinfo; scalar_t__ nmsgs; int nsubxacts; scalar_t__ dbId; int /*<<< orphan*/ * subxacts; int /*<<< orphan*/  msgs; int /*<<< orphan*/  origin_timestamp; int /*<<< orphan*/  origin_lsn; int /*<<< orphan*/  xact_time; } ;
typedef  TYPE_3__ xl_xact_parsed_commit ;
struct TYPE_13__ {int /*<<< orphan*/  endptr; int /*<<< orphan*/  origptr; int /*<<< orphan*/  record; } ;
typedef  TYPE_4__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_14__ {int /*<<< orphan*/  reorder; scalar_t__ fast_forward; TYPE_2__* slot; int /*<<< orphan*/  snapshot_builder; } ;
struct TYPE_10__ {scalar_t__ database; } ;
struct TYPE_11__ {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  RepOriginId ;
typedef  TYPE_5__ LogicalDecodingContext ;

/* Variables and functions */
 scalar_t__ FilterByOrigin (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ReorderBufferAddInvalidations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferCommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferCommitChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferForget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferXidSetCatalogChanges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapBuildCommitTxn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SnapBuildXactNeedsSkip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XACT_XINFO_HAS_ORIGIN ; 
 int /*<<< orphan*/  XLogRecGetOrigin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DecodeCommit(LogicalDecodingContext *ctx, XLogRecordBuffer *buf,
			 xl_xact_parsed_commit *parsed, TransactionId xid)
{
	XLogRecPtr	origin_lsn = InvalidXLogRecPtr;
	TimestampTz commit_time = parsed->xact_time;
	RepOriginId origin_id = XLogRecGetOrigin(buf->record);
	int			i;

	if (parsed->xinfo & XACT_XINFO_HAS_ORIGIN)
	{
		origin_lsn = parsed->origin_lsn;
		commit_time = parsed->origin_timestamp;
	}

	/*
	 * Process invalidation messages, even if we're not interested in the
	 * transaction's contents, since the various caches need to always be
	 * consistent.
	 */
	if (parsed->nmsgs > 0)
	{
		if (!ctx->fast_forward)
			ReorderBufferAddInvalidations(ctx->reorder, xid, buf->origptr,
										  parsed->nmsgs, parsed->msgs);
		ReorderBufferXidSetCatalogChanges(ctx->reorder, xid, buf->origptr);
	}

	SnapBuildCommitTxn(ctx->snapshot_builder, buf->origptr, xid,
					   parsed->nsubxacts, parsed->subxacts);

	/* ----
	 * Check whether we are interested in this specific transaction, and tell
	 * the reorderbuffer to forget the content of the (sub-)transactions
	 * if not.
	 *
	 * There can be several reasons we might not be interested in this
	 * transaction:
	 * 1) We might not be interested in decoding transactions up to this
	 *	  LSN. This can happen because we previously decoded it and now just
	 *	  are restarting or if we haven't assembled a consistent snapshot yet.
	 * 2) The transaction happened in another database.
	 * 3) The output plugin is not interested in the origin.
	 * 4) We are doing fast-forwarding
	 *
	 * We can't just use ReorderBufferAbort() here, because we need to execute
	 * the transaction's invalidations.  This currently won't be needed if
	 * we're just skipping over the transaction because currently we only do
	 * so during startup, to get to the first transaction the client needs. As
	 * we have reset the catalog caches before starting to read WAL, and we
	 * haven't yet touched any catalogs, there can't be anything to invalidate.
	 * But if we're "forgetting" this commit because it's it happened in
	 * another database, the invalidations might be important, because they
	 * could be for shared catalogs and we might have loaded data into the
	 * relevant syscaches.
	 * ---
	 */
	if (SnapBuildXactNeedsSkip(ctx->snapshot_builder, buf->origptr) ||
		(parsed->dbId != InvalidOid && parsed->dbId != ctx->slot->data.database) ||
		ctx->fast_forward || FilterByOrigin(ctx, origin_id))
	{
		for (i = 0; i < parsed->nsubxacts; i++)
		{
			ReorderBufferForget(ctx->reorder, parsed->subxacts[i], buf->origptr);
		}
		ReorderBufferForget(ctx->reorder, xid, buf->origptr);

		return;
	}

	/* tell the reorderbuffer about the surviving subtransactions */
	for (i = 0; i < parsed->nsubxacts; i++)
	{
		ReorderBufferCommitChild(ctx->reorder, xid, parsed->subxacts[i],
								 buf->origptr, buf->endptr);
	}

	/* replay actions of all transaction + subtransactions in order */
	ReorderBufferCommit(ctx->reorder, xid, buf->origptr, buf->endptr,
						commit_time, origin_id, origin_lsn);
}