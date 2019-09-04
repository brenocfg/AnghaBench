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
struct trace_seq {scalar_t__ len; int /*<<< orphan*/  buffer; } ;
struct tep_record {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct perf_evsel {int /*<<< orphan*/  tp_format; } ;
struct hist_entry {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; int /*<<< orphan*/  hists; } ;
struct TYPE_2__ {scalar_t__ raw_trace; } ;

/* Variables and functions */
 struct perf_evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 char* realloc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  tep_event_info (struct trace_seq*,int /*<<< orphan*/ ,struct tep_record*) ; 
 int /*<<< orphan*/  tep_print_fields (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

__attribute__((used)) static char *get_trace_output(struct hist_entry *he)
{
	struct trace_seq seq;
	struct perf_evsel *evsel;
	struct tep_record rec = {
		.data = he->raw_data,
		.size = he->raw_size,
	};

	evsel = hists_to_evsel(he->hists);

	trace_seq_init(&seq);
	if (symbol_conf.raw_trace) {
		tep_print_fields(&seq, he->raw_data, he->raw_size,
				 evsel->tp_format);
	} else {
		tep_event_info(&seq, evsel->tp_format, &rec);
	}
	/*
	 * Trim the buffer, it starts at 4KB and we're not going to
	 * add anything more to this buffer.
	 */
	return realloc(seq.buffer, seq.len + 1);
}