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
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_1__ machines; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t machine__fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t perf_session__fprintf(struct perf_session *session, FILE *fp)
{
	/*
	 * FIXME: Here we have to actually print all the machines in this
	 * session, not just the host...
	 */
	return machine__fprintf(&session->machines.host, fp);
}