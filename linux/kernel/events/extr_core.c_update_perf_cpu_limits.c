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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  perf_sample_allowed_ns ; 
 int perf_sample_period_ns ; 
 int sysctl_perf_cpu_time_max_percent ; 

__attribute__((used)) static void update_perf_cpu_limits(void)
{
	u64 tmp = perf_sample_period_ns;

	tmp *= sysctl_perf_cpu_time_max_percent;
	tmp = div_u64(tmp, 100);
	if (!tmp)
		tmp = 1;

	WRITE_ONCE(perf_sample_allowed_ns, tmp);
}