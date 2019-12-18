#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_progress {int dummy; } ;
struct reader {scalar_t__ data_size; int /*<<< orphan*/  process; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  fd; } ;
struct perf_tool {int /*<<< orphan*/  no_warn; } ;
struct ordered_events {int dummy; } ;
struct TYPE_2__ {scalar_t__ data_size; int /*<<< orphan*/  data_offset; } ;
struct perf_session {int one_mmap; struct ordered_events ordered_events; struct perf_tool* tool; TYPE_1__ header; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OE_FLUSH__FINAL ; 
 int auxtrace__flush_events (struct perf_session*,struct perf_tool*) ; 
 int /*<<< orphan*/  auxtrace__free_events (struct perf_session*) ; 
 int ordered_events__flush (struct ordered_events*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_events__reinit (struct ordered_events*) ; 
 int /*<<< orphan*/  perf_data__fd (int /*<<< orphan*/ ) ; 
 int perf_session__flush_thread_stacks (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__warn_about_errors (struct perf_session*) ; 
 int /*<<< orphan*/  perf_tool__fill_defaults (struct perf_tool*) ; 
 int /*<<< orphan*/  process_simple ; 
 int reader__process_events (struct reader*,struct perf_session*,struct ui_progress*) ; 
 int /*<<< orphan*/  ui_progress__finish () ; 
 int /*<<< orphan*/  ui_progress__init_size (struct ui_progress*,scalar_t__,char*) ; 

__attribute__((used)) static int __perf_session__process_events(struct perf_session *session)
{
	struct reader rd = {
		.fd		= perf_data__fd(session->data),
		.data_size	= session->header.data_size,
		.data_offset	= session->header.data_offset,
		.process	= process_simple,
	};
	struct ordered_events *oe = &session->ordered_events;
	struct perf_tool *tool = session->tool;
	struct ui_progress prog;
	int err;

	perf_tool__fill_defaults(tool);

	if (rd.data_size == 0)
		return -1;

	ui_progress__init_size(&prog, rd.data_size, "Processing events...");

	err = reader__process_events(&rd, session, &prog);
	if (err)
		goto out_err;
	/* do the final flush for ordered samples */
	err = ordered_events__flush(oe, OE_FLUSH__FINAL);
	if (err)
		goto out_err;
	err = auxtrace__flush_events(session, tool);
	if (err)
		goto out_err;
	err = perf_session__flush_thread_stacks(session);
out_err:
	ui_progress__finish();
	if (!tool->no_warn)
		perf_session__warn_about_errors(session);
	/*
	 * We may switching perf.data output, make ordered_events
	 * reusable.
	 */
	ordered_events__reinit(&session->ordered_events);
	auxtrace__free_events(session);
	session->one_mmap = false;
	return err;
}