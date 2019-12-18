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
struct perf_session {int /*<<< orphan*/  evlist; } ;
struct perf_data {scalar_t__ path; } ;
struct TYPE_4__ {int record; struct perf_session* session; struct perf_data data; } ;
struct TYPE_3__ {int run_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  evsel_list ; 
 scalar_t__ forever ; 
 int /*<<< orphan*/  init_features (struct perf_session*) ; 
 scalar_t__ output_name ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__ perf_stat ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ stat_config ; 
 int /*<<< orphan*/  stat_options ; 
 int /*<<< orphan*/  stat_record_usage ; 

__attribute__((used)) static int __cmd_record(int argc, const char **argv)
{
	struct perf_session *session;
	struct perf_data *data = &perf_stat.data;

	argc = parse_options(argc, argv, stat_options, stat_record_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	if (output_name)
		data->path = output_name;

	if (stat_config.run_count != 1 || forever) {
		pr_err("Cannot use -r option with perf stat record.\n");
		return -1;
	}

	session = perf_session__new(data, false, NULL);
	if (IS_ERR(session)) {
		pr_err("Perf session creation failed\n");
		return PTR_ERR(session);
	}

	init_features(session);

	session->evlist   = evsel_list;
	perf_stat.session = session;
	perf_stat.record  = true;
	return argc;
}