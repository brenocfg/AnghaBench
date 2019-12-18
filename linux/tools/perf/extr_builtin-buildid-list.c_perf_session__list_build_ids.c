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
struct perf_session {int /*<<< orphan*/  header; } ;
struct perf_data {int force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_AUXTRACE ; 
 scalar_t__ IS_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  build_id__mark_dso_hit_ops ; 
 int /*<<< orphan*/  dso__skip_buildid ; 
 scalar_t__ filename__fprintf_build_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_name ; 
 scalar_t__ perf_data__is_pipe (struct perf_data*) ; 
 scalar_t__ perf_header__has_feat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__fprintf_dsos_buildid (struct perf_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__process_events (struct perf_session*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  symbol__elf_init () ; 

__attribute__((used)) static int perf_session__list_build_ids(bool force, bool with_hits)
{
	struct perf_session *session;
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = force,
	};

	symbol__elf_init();
	/*
	 * See if this is an ELF file first:
	 */
	if (filename__fprintf_build_id(input_name, stdout) > 0)
		goto out;

	session = perf_session__new(&data, false, &build_id__mark_dso_hit_ops);
	if (IS_ERR(session))
		return PTR_ERR(session);

	/*
	 * We take all buildids when the file contains AUX area tracing data
	 * because we do not decode the trace because it would take too long.
	 */
	if (!perf_data__is_pipe(&data) &&
	    perf_header__has_feat(&session->header, HEADER_AUXTRACE))
		with_hits = false;

	/*
	 * in pipe-mode, the only way to get the buildids is to parse
	 * the record stream. Buildids are stored as RECORD_HEADER_BUILD_ID
	 */
	if (with_hits || perf_data__is_pipe(&data))
		perf_session__process_events(session);

	perf_session__fprintf_dsos_buildid(session, stdout, dso__skip_buildid, with_hits);
	perf_session__delete(session);
out:
	return 0;
}