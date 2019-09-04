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
typedef  int /*<<< orphan*/  u64 ;
struct perf_session {int dummy; } ;
struct perf_event_attr {int dummy; } ;
struct cs_etm_synth {int /*<<< orphan*/  dummy_tool; struct perf_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_etm__event_synth ; 
 int /*<<< orphan*/  memset (struct cs_etm_synth*,int /*<<< orphan*/ ,int) ; 
 int perf_event__synthesize_attr (int /*<<< orphan*/ *,struct perf_event_attr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_etm__synth_event(struct perf_session *session,
			       struct perf_event_attr *attr, u64 id)
{
	struct cs_etm_synth cs_etm_synth;

	memset(&cs_etm_synth, 0, sizeof(struct cs_etm_synth));
	cs_etm_synth.session = session;

	return perf_event__synthesize_attr(&cs_etm_synth.dummy_tool, attr, 1,
					   &id, cs_etm__event_synth);
}