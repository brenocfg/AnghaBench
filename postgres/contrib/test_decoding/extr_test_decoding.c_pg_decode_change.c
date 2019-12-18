#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_20__ {int xact_wrote_changes; int /*<<< orphan*/  context; scalar_t__ skip_empty_xacts; } ;
typedef  TYPE_5__ TestDecodingData ;
struct TYPE_23__ {int /*<<< orphan*/  relname; scalar_t__ relrewrite; } ;
struct TYPE_22__ {int /*<<< orphan*/  out; TYPE_5__* output_plugin_private; } ;
struct TYPE_18__ {TYPE_2__* oldtuple; TYPE_1__* newtuple; } ;
struct TYPE_19__ {TYPE_3__ tp; } ;
struct TYPE_21__ {int action; TYPE_4__ data; } ;
struct TYPE_17__ {int /*<<< orphan*/  tuple; } ;
struct TYPE_16__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  ReorderBufferTXN ;
typedef  TYPE_6__ ReorderBufferChange ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_7__ LogicalDecodingContext ;
typedef  TYPE_8__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutputPluginPrepareWrite (TYPE_7__*,int) ; 
 int /*<<< orphan*/  OutputPluginWrite (TYPE_7__*,int) ; 
#define  REORDER_BUFFER_CHANGE_DELETE 130 
#define  REORDER_BUFFER_CHANGE_INSERT 129 
#define  REORDER_BUFFER_CHANGE_UPDATE 128 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_8__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (scalar_t__) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_output_begin (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 char* quote_qualified_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuple_to_stringinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pg_decode_change(LogicalDecodingContext *ctx, ReorderBufferTXN *txn,
				 Relation relation, ReorderBufferChange *change)
{
	TestDecodingData *data;
	Form_pg_class class_form;
	TupleDesc	tupdesc;
	MemoryContext old;

	data = ctx->output_plugin_private;

	/* output BEGIN if we haven't yet */
	if (data->skip_empty_xacts && !data->xact_wrote_changes)
	{
		pg_output_begin(ctx, data, txn, false);
	}
	data->xact_wrote_changes = true;

	class_form = RelationGetForm(relation);
	tupdesc = RelationGetDescr(relation);

	/* Avoid leaking memory by using and resetting our own context */
	old = MemoryContextSwitchTo(data->context);

	OutputPluginPrepareWrite(ctx, true);

	appendStringInfoString(ctx->out, "table ");
	appendStringInfoString(ctx->out,
						   quote_qualified_identifier(
													  get_namespace_name(
																		 get_rel_namespace(RelationGetRelid(relation))),
													  class_form->relrewrite ?
													  get_rel_name(class_form->relrewrite) :
													  NameStr(class_form->relname)));
	appendStringInfoChar(ctx->out, ':');

	switch (change->action)
	{
		case REORDER_BUFFER_CHANGE_INSERT:
			appendStringInfoString(ctx->out, " INSERT:");
			if (change->data.tp.newtuple == NULL)
				appendStringInfoString(ctx->out, " (no-tuple-data)");
			else
				tuple_to_stringinfo(ctx->out, tupdesc,
									&change->data.tp.newtuple->tuple,
									false);
			break;
		case REORDER_BUFFER_CHANGE_UPDATE:
			appendStringInfoString(ctx->out, " UPDATE:");
			if (change->data.tp.oldtuple != NULL)
			{
				appendStringInfoString(ctx->out, " old-key:");
				tuple_to_stringinfo(ctx->out, tupdesc,
									&change->data.tp.oldtuple->tuple,
									true);
				appendStringInfoString(ctx->out, " new-tuple:");
			}

			if (change->data.tp.newtuple == NULL)
				appendStringInfoString(ctx->out, " (no-tuple-data)");
			else
				tuple_to_stringinfo(ctx->out, tupdesc,
									&change->data.tp.newtuple->tuple,
									false);
			break;
		case REORDER_BUFFER_CHANGE_DELETE:
			appendStringInfoString(ctx->out, " DELETE:");

			/* if there was no PK, we only know that a delete happened */
			if (change->data.tp.oldtuple == NULL)
				appendStringInfoString(ctx->out, " (no-tuple-data)");
			/* In DELETE, only the replica identity is present; display that */
			else
				tuple_to_stringinfo(ctx->out, tupdesc,
									&change->data.tp.oldtuple->tuple,
									true);
			break;
		default:
			Assert(false);
	}

	MemoryContextSwitchTo(old);
	MemoryContextReset(data->context);

	OutputPluginWrite(ctx, true);
}