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
struct result {int member_0; int member_1; char* member_2; char* member_3; char* member_4; } ;
struct machine {int dummy; } ;
struct hists {int dummy; } ;
struct evsel {int dummy; } ;
struct TYPE_2__ {int use_callchain; int cumulate_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct result*) ; 
 int /*<<< orphan*/  CALLCHAIN ; 
 int add_hist_entries (struct hists*,struct machine*) ; 
 int /*<<< orphan*/  callchain_param ; 
 int /*<<< orphan*/  callchain_register_param (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_hist_entries (struct hists*) ; 
 int do_test (struct hists*,struct result*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hists* evsel__hists (struct evsel*) ; 
 int /*<<< orphan*/  perf_evsel__reset_sample_bit (struct evsel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_output_field () ; 
 int /*<<< orphan*/  setup_sorting (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int test3(struct evsel *evsel, struct machine *machine)
{
	int err;
	struct hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Children      Self  Command  Shared Object                   Symbol
	 * ========  ========  =======  =============  =======================
	 *   70.00%    20.00%     perf  perf           [.] main
	 *   50.00%     0.00%     perf  perf           [.] run_command
	 *   30.00%    10.00%     bash  bash           [.] main
	 *   30.00%    10.00%     perf  perf           [.] cmd_record
	 *   20.00%     0.00%     bash  libc           [.] malloc
	 *   10.00%    10.00%     bash  [kernel]       [k] page_fault
	 *   10.00%    10.00%     bash  bash           [.] xmalloc
	 *   10.00%    10.00%     perf  [kernel]       [k] page_fault
	 *   10.00%    10.00%     perf  libc           [.] malloc
	 *   10.00%    10.00%     perf  [kernel]       [k] schedule
	 *   10.00%    10.00%     perf  libc           [.] free
	 *   10.00%     0.00%     perf  [kernel]       [k] sys_perf_event_open
	 */
	struct result expected[] = {
		{ 7000, 2000, "perf", "perf",     "main" },
		{ 5000,    0, "perf", "perf",     "run_command" },
		{ 3000, 1000, "bash", "bash",     "main" },
		{ 3000, 1000, "perf", "perf",     "cmd_record" },
		{ 2000,    0, "bash", "libc",     "malloc" },
		{ 1000, 1000, "bash", "[kernel]", "page_fault" },
		{ 1000, 1000, "bash", "bash",     "xmalloc" },
		{ 1000, 1000, "perf", "[kernel]", "page_fault" },
		{ 1000, 1000, "perf", "[kernel]", "schedule" },
		{ 1000, 1000, "perf", "libc",     "free" },
		{ 1000, 1000, "perf", "libc",     "malloc" },
		{ 1000,    0, "perf", "[kernel]", "sys_perf_event_open" },
	};

	symbol_conf.use_callchain = false;
	symbol_conf.cumulate_callchain = true;
	perf_evsel__reset_sample_bit(evsel, CALLCHAIN);

	setup_sorting(NULL);
	callchain_register_param(&callchain_param);

	err = add_hist_entries(hists, machine);
	if (err < 0)
		goto out;

	err = do_test(hists, expected, ARRAY_SIZE(expected), NULL, 0);

out:
	del_hist_entries(hists);
	reset_output_field();
	return err;
}