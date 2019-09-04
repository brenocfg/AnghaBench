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
 int machines__for_each_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__flush_thread_stack ; 

__attribute__((used)) static int perf_session__flush_thread_stacks(struct perf_session *session)
{
	return machines__for_each_thread(&session->machines,
					 perf_session__flush_thread_stack,
					 NULL);
}