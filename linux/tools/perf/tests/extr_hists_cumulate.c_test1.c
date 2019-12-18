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
struct result {int member_1; char* member_2; char* member_3; char* member_4; int /*<<< orphan*/  member_0; } ;
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

__attribute__((used)) static int test1(struct evsel *evsel, struct machine *machine)
{
	int err;
	struct hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Overhead  Command  Shared Object          Symbol
	 * ========  =======  =============  ==============
	 *   20.00%     perf  perf           [.] main
	 *   10.00%     bash  [kernel]       [k] page_fault
	 *   10.00%     bash  bash           [.] main
	 *   10.00%     bash  bash           [.] xmalloc
	 *   10.00%     perf  [kernel]       [k] page_fault
	 *   10.00%     perf  [kernel]       [k] schedule
	 *   10.00%     perf  libc           [.] free
	 *   10.00%     perf  libc           [.] malloc
	 *   10.00%     perf  perf           [.] cmd_record
	 */
	struct result expected[] = {
		{ 0, 2000, "perf", "perf",     "main" },
		{ 0, 1000, "bash", "[kernel]", "page_fault" },
		{ 0, 1000, "bash", "bash",     "main" },
		{ 0, 1000, "bash", "bash",     "xmalloc" },
		{ 0, 1000, "perf", "[kernel]", "page_fault" },
		{ 0, 1000, "perf", "[kernel]", "schedule" },
		{ 0, 1000, "perf", "libc",     "free" },
		{ 0, 1000, "perf", "libc",     "malloc" },
		{ 0, 1000, "perf", "perf",     "cmd_record" },
	};

	symbol_conf.use_callchain = false;
	symbol_conf.cumulate_callchain = false;
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