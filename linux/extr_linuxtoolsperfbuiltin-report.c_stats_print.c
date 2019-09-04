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
struct report {struct perf_session* session; } ;
struct perf_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_session__fprintf_nr_events (struct perf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int stats_print(struct report *rep)
{
	struct perf_session *session = rep->session;

	perf_session__fprintf_nr_events(session, stdout);
	return 0;
}