#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_session {int /*<<< orphan*/  evlist; int /*<<< orphan*/  header; struct perf_data* data; } ;
struct perf_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_STAT ; 
 scalar_t__ perf_data__is_pipe (struct perf_data*) ; 
 int /*<<< orphan*/  perf_evlist__valid_read_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__valid_sample_id_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__valid_sample_type (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_header__has_feat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__read_header (struct perf_session*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int perf_session__open(struct perf_session *session)
{
	struct perf_data *data = session->data;

	if (perf_session__read_header(session) < 0) {
		pr_err("incompatible file format (rerun with -v to learn more)\n");
		return -1;
	}

	if (perf_data__is_pipe(data))
		return 0;

	if (perf_header__has_feat(&session->header, HEADER_STAT))
		return 0;

	if (!perf_evlist__valid_sample_type(session->evlist)) {
		pr_err("non matching sample_type\n");
		return -1;
	}

	if (!perf_evlist__valid_sample_id_all(session->evlist)) {
		pr_err("non matching sample_id_all\n");
		return -1;
	}

	if (!perf_evlist__valid_read_format(session->evlist)) {
		pr_err("non matching read_format\n");
		return -1;
	}

	return 0;
}