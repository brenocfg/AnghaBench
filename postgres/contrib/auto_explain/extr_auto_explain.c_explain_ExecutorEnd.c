#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {double total; } ;
struct TYPE_21__ {int analyze; int buffers; int timing; int summary; TYPE_1__* str; scalar_t__ costs; int /*<<< orphan*/  settings; scalar_t__ format; int /*<<< orphan*/  verbose; } ;
struct TYPE_20__ {scalar_t__ instrument_options; TYPE_8__* totaltime; } ;
struct TYPE_19__ {int len; char* data; } ;
typedef  TYPE_2__ QueryDesc ;
typedef  TYPE_3__ ExplainState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_JSON ; 
 int /*<<< orphan*/  ExplainBeginOutput (TYPE_3__*) ; 
 int /*<<< orphan*/  ExplainEndOutput (TYPE_3__*) ; 
 int /*<<< orphan*/  ExplainPrintJITSummary (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainPrintPlan (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainPrintTriggers (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainQueryText (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  InstrEndLoop (TYPE_8__*) ; 
 TYPE_3__* NewExplainState () ; 
 scalar_t__ auto_explain_enabled () ; 
 scalar_t__ auto_explain_log_analyze ; 
 scalar_t__ auto_explain_log_buffers ; 
 scalar_t__ auto_explain_log_format ; 
 int /*<<< orphan*/  auto_explain_log_level ; 
 double auto_explain_log_min_duration ; 
 int /*<<< orphan*/  auto_explain_log_settings ; 
 scalar_t__ auto_explain_log_timing ; 
 scalar_t__ auto_explain_log_triggers ; 
 int /*<<< orphan*/  auto_explain_log_verbose ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhidestmt (int) ; 
 int /*<<< orphan*/  errmsg (char*,double,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  prev_ExecutorEnd (TYPE_2__*) ; 
 int /*<<< orphan*/  standard_ExecutorEnd (TYPE_2__*) ; 

__attribute__((used)) static void
explain_ExecutorEnd(QueryDesc *queryDesc)
{
	if (queryDesc->totaltime && auto_explain_enabled())
	{
		double		msec;

		/*
		 * Make sure stats accumulation is done.  (Note: it's okay if several
		 * levels of hook all do this.)
		 */
		InstrEndLoop(queryDesc->totaltime);

		/* Log plan if duration is exceeded. */
		msec = queryDesc->totaltime->total * 1000.0;
		if (msec >= auto_explain_log_min_duration)
		{
			ExplainState *es = NewExplainState();

			es->analyze = (queryDesc->instrument_options && auto_explain_log_analyze);
			es->verbose = auto_explain_log_verbose;
			es->buffers = (es->analyze && auto_explain_log_buffers);
			es->timing = (es->analyze && auto_explain_log_timing);
			es->summary = es->analyze;
			es->format = auto_explain_log_format;
			es->settings = auto_explain_log_settings;

			ExplainBeginOutput(es);
			ExplainQueryText(es, queryDesc);
			ExplainPrintPlan(es, queryDesc);
			if (es->analyze && auto_explain_log_triggers)
				ExplainPrintTriggers(es, queryDesc);
			if (es->costs)
				ExplainPrintJITSummary(es, queryDesc);
			ExplainEndOutput(es);

			/* Remove last line break */
			if (es->str->len > 0 && es->str->data[es->str->len - 1] == '\n')
				es->str->data[--es->str->len] = '\0';

			/* Fix JSON to output an object */
			if (auto_explain_log_format == EXPLAIN_FORMAT_JSON)
			{
				es->str->data[0] = '{';
				es->str->data[es->str->len - 1] = '}';
			}

			/*
			 * Note: we rely on the existing logging of context or
			 * debug_query_string to identify just which statement is being
			 * reported.  This isn't ideal but trying to do it here would
			 * often result in duplication.
			 */
			ereport(auto_explain_log_level,
					(errmsg("duration: %.3f ms  plan:\n%s",
							msec, es->str->data),
					 errhidestmt(true)));

			pfree(es->str->data);
		}
	}

	if (prev_ExecutorEnd)
		prev_ExecutorEnd(queryDesc);
	else
		standard_ExecutorEnd(queryDesc);
}