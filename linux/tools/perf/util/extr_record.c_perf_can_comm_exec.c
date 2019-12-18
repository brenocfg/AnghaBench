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
 int perf_probe_api (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_probe_comm_exec ; 

__attribute__((used)) static bool perf_can_comm_exec(void)
{
	return perf_probe_api(perf_probe_comm_exec);
}