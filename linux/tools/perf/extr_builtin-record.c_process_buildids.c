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
struct TYPE_3__ {int /*<<< orphan*/ * sample; } ;
struct record {TYPE_1__ tool; int /*<<< orphan*/  timestamp_boundary; scalar_t__ buildid_all; int /*<<< orphan*/  data; struct perf_session* session; } ;
struct perf_session {int dummy; } ;
struct TYPE_4__ {int ignore_vmlinux_buildid; } ;

/* Variables and functions */
 scalar_t__ perf_data__size (int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static int process_buildids(struct record *rec)
{
	struct perf_session *session = rec->session;

	if (perf_data__size(&rec->data) == 0)
		return 0;

	/*
	 * During this process, it'll load kernel map and replace the
	 * dso->long_name to a real pathname it found.  In this case
	 * we prefer the vmlinux path like
	 *   /lib/modules/3.16.4/build/vmlinux
	 *
	 * rather than build-id path (in debug directory).
	 *   $HOME/.debug/.build-id/f0/6e17aa50adf4d00b88925e03775de107611551
	 */
	symbol_conf.ignore_vmlinux_buildid = true;

	/*
	 * If --buildid-all is given, it marks all DSO regardless of hits,
	 * so no need to process samples. But if timestamp_boundary is enabled,
	 * it still needs to walk on all samples to get the timestamps of
	 * first/last samples.
	 */
	if (rec->buildid_all && !rec->timestamp_boundary)
		rec->tool.sample = NULL;

	return perf_session__process_events(session);
}