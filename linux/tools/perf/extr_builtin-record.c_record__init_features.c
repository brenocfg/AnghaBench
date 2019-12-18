#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ clockid_res_ns; scalar_t__ use_clockid; int /*<<< orphan*/  full_auxtrace; int /*<<< orphan*/  branch_stack; } ;
struct record {TYPE_3__ opts; TYPE_2__* evlist; scalar_t__ no_buildid; struct perf_session* session; } ;
struct perf_session {int /*<<< orphan*/  header; } ;
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
struct TYPE_5__ {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_AUXTRACE ; 
 int /*<<< orphan*/  HEADER_BRANCH_STACK ; 
 int /*<<< orphan*/  HEADER_BUILD_ID ; 
 int /*<<< orphan*/  HEADER_CLOCKID ; 
 int /*<<< orphan*/  HEADER_COMPRESSED ; 
 int /*<<< orphan*/  HEADER_DIR_FORMAT ; 
 int HEADER_FIRST_FEATURE ; 
 int HEADER_LAST_FEATURE ; 
 int /*<<< orphan*/  HEADER_STAT ; 
 int /*<<< orphan*/  HEADER_TRACING_DATA ; 
 int /*<<< orphan*/  have_tracepoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_header__clear_feat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_header__set_feat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  record__comp_enabled (struct record*) ; 

__attribute__((used)) static void record__init_features(struct record *rec)
{
	struct perf_session *session = rec->session;
	int feat;

	for (feat = HEADER_FIRST_FEATURE; feat < HEADER_LAST_FEATURE; feat++)
		perf_header__set_feat(&session->header, feat);

	if (rec->no_buildid)
		perf_header__clear_feat(&session->header, HEADER_BUILD_ID);

	if (!have_tracepoints(&rec->evlist->core.entries))
		perf_header__clear_feat(&session->header, HEADER_TRACING_DATA);

	if (!rec->opts.branch_stack)
		perf_header__clear_feat(&session->header, HEADER_BRANCH_STACK);

	if (!rec->opts.full_auxtrace)
		perf_header__clear_feat(&session->header, HEADER_AUXTRACE);

	if (!(rec->opts.use_clockid && rec->opts.clockid_res_ns))
		perf_header__clear_feat(&session->header, HEADER_CLOCKID);

	perf_header__clear_feat(&session->header, HEADER_DIR_FORMAT);
	if (!record__comp_enabled(rec))
		perf_header__clear_feat(&session->header, HEADER_COMPRESSED);

	perf_header__clear_feat(&session->header, HEADER_STAT);
}