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
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned long long* cpustat; } ;

/* Variables and functions */
 size_t CPUTIME_IOWAIT ; 
 unsigned long long NSEC_PER_USEC ; 
 scalar_t__ cpu_online (int) ; 
 unsigned long long get_cpu_iowait_time_us (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ kcpustat_cpu (int) ; 

__attribute__((used)) static u64 get_iowait_time(int cpu)
{
	u64 iowait, iowait_usecs = -1ULL;

	if (cpu_online(cpu))
		iowait_usecs = get_cpu_iowait_time_us(cpu, NULL);

	if (iowait_usecs == -1ULL)
		/* !NO_HZ or cpu offline so we can rely on cpustat.iowait */
		iowait = kcpustat_cpu(cpu).cpustat[CPUTIME_IOWAIT];
	else
		iowait = iowait_usecs * NSEC_PER_USEC;

	return iowait;
}