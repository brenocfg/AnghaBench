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
struct TYPE_2__ {int /*<<< orphan*/  has_br_stack; } ;

/* Variables and functions */
 scalar_t__ COMPUTE_CYCLES ; 
 int /*<<< orphan*/  SORT_MODE__DIFF ; 
 int __cmd_diff () ; 
 scalar_t__ check_file_brstack () ; 
 scalar_t__ compute ; 
 scalar_t__ data_init (int,char const**) ; 
 int /*<<< orphan*/  diff__config ; 
 int /*<<< orphan*/  diff_usage ; 
 int hists__init () ; 
 int /*<<< orphan*/  options ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ pdiff ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_quiet_option () ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  setup_pager () ; 
 scalar_t__ setup_sorting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort__mode ; 
 int /*<<< orphan*/  sort__setup_elide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__annotation_init () ; 
 scalar_t__ symbol__init (int /*<<< orphan*/ *) ; 
 scalar_t__ ui_init () ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cmd_diff(int argc, const char **argv)
{
	int ret = hists__init();

	if (ret < 0)
		return ret;

	perf_config(diff__config, NULL);

	argc = parse_options(argc, argv, options, diff_usage, 0);

	if (quiet)
		perf_quiet_option();

	symbol__annotation_init();

	if (symbol__init(NULL) < 0)
		return -1;

	if (data_init(argc, argv) < 0)
		return -1;

	if (check_file_brstack() < 0)
		return -1;

	if (compute == COMPUTE_CYCLES && !pdiff.has_br_stack)
		return -1;

	if (ui_init() < 0)
		return -1;

	sort__mode = SORT_MODE__DIFF;

	if (setup_sorting(NULL) < 0)
		usage_with_options(diff_usage, options);

	setup_pager();

	sort__setup_elide(NULL);

	return __cmd_diff();
}