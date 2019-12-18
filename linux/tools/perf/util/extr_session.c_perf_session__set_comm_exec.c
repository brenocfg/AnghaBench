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
struct perf_session {int /*<<< orphan*/  machines; } ;

/* Variables and functions */
 int /*<<< orphan*/  machines__set_comm_exec (int /*<<< orphan*/ *,int) ; 
 int perf_session__has_comm_exec (struct perf_session*) ; 

__attribute__((used)) static void perf_session__set_comm_exec(struct perf_session *session)
{
	bool comm_exec = perf_session__has_comm_exec(session);

	machines__set_comm_exec(&session->machines, comm_exec);
}