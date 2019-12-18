#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  returned_rows; int /*<<< orphan*/  tupdesc; int /*<<< orphan*/  tupstore; int /*<<< orphan*/  binary_output; } ;
struct TYPE_6__ {TYPE_1__* out; scalar_t__ output_writer_private; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ LogicalDecodingContext ;
typedef  TYPE_3__ DecodingOutputState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetDatabaseEncoding () ; 
 int /*<<< orphan*/  LSNGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ MaxAllocSize ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  cstring_to_text_with_len (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_verify_mbstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  tuplestore_putvalues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
LogicalOutputWrite(LogicalDecodingContext *ctx, XLogRecPtr lsn, TransactionId xid,
				   bool last_write)
{
	Datum		values[3];
	bool		nulls[3];
	DecodingOutputState *p;

	/* SQL Datums can only be of a limited length... */
	if (ctx->out->len > MaxAllocSize - VARHDRSZ)
		elog(ERROR, "too much output for sql interface");

	p = (DecodingOutputState *) ctx->output_writer_private;

	memset(nulls, 0, sizeof(nulls));
	values[0] = LSNGetDatum(lsn);
	values[1] = TransactionIdGetDatum(xid);

	/*
	 * Assert ctx->out is in database encoding when we're writing textual
	 * output.
	 */
	if (!p->binary_output)
		Assert(pg_verify_mbstr(GetDatabaseEncoding(),
							   ctx->out->data, ctx->out->len,
							   false));

	/* ick, but cstring_to_text_with_len works for bytea perfectly fine */
	values[2] = PointerGetDatum(
								cstring_to_text_with_len(ctx->out->data, ctx->out->len));

	tuplestore_putvalues(p->tupstore, p->tupdesc, values, nulls);
	p->returned_rows++;
}