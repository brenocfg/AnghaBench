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

/* Variables and functions */
 int /*<<< orphan*/  have_frontend_stalled ; 
 int /*<<< orphan*/  pmu_have_event (char*,char*) ; 
 int /*<<< orphan*/  rt_stat ; 
 int /*<<< orphan*/  runtime_stat__init (int /*<<< orphan*/ *) ; 

void perf_stat__init_shadow_stats(void)
{
	have_frontend_stalled = pmu_have_event("cpu", "stalled-cycles-frontend");
	runtime_stat__init(&rt_stat);
}