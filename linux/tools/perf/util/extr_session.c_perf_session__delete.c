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
struct TYPE_2__ {int /*<<< orphan*/  env; } ;
struct perf_session {scalar_t__ data; int /*<<< orphan*/  machines; TYPE_1__ header; int /*<<< orphan*/  auxtrace_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace__free (struct perf_session*) ; 
 int /*<<< orphan*/  auxtrace_index__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_session*) ; 
 int /*<<< orphan*/  machines__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_data__close (scalar_t__) ; 
 int /*<<< orphan*/  perf_env__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__delete_threads (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__destroy_kernel_maps (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__release_decomp_events (struct perf_session*) ; 

void perf_session__delete(struct perf_session *session)
{
	if (session == NULL)
		return;
	auxtrace__free(session);
	auxtrace_index__free(&session->auxtrace_index);
	perf_session__destroy_kernel_maps(session);
	perf_session__delete_threads(session);
	perf_session__release_decomp_events(session);
	perf_env__exit(&session->header.env);
	machines__exit(&session->machines);
	if (session->data)
		perf_data__close(session->data);
	free(session);
}