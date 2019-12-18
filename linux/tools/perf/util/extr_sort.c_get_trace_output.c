#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_seq {scalar_t__ len; int /*<<< orphan*/  buffer; } ;
struct tep_record {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct hist_entry {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; int /*<<< orphan*/  hists; } ;
struct evsel {TYPE_1__* tp_format; } ;
struct TYPE_4__ {scalar_t__ raw_trace; } ;
struct TYPE_3__ {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEP_PRINT_INFO ; 
 struct evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 char* realloc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__ symbol_conf ; 
 int /*<<< orphan*/  tep_print_event (int /*<<< orphan*/ ,struct trace_seq*,struct tep_record*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_print_fields (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

__attribute__((used)) static char *get_trace_output(struct hist_entry *he)
{
	struct trace_seq seq;
	struct evsel *evsel;
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
		tep_print_event(evsel->tp_format->tep,
				&seq, &rec, "%s", TEP_PRINT_INFO);
	}
	/*
	 * Trim the buffer, it starts at 4KB and we're not going to
	 * add anything more to this buffer.
	 */
	return realloc(seq.buffer, seq.len + 1);
}