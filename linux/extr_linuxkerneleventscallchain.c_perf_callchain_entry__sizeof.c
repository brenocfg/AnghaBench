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
struct perf_callchain_entry {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int sysctl_perf_event_max_contexts_per_stack ; 
 int sysctl_perf_event_max_stack ; 

__attribute__((used)) static inline size_t perf_callchain_entry__sizeof(void)
{
	return (sizeof(struct perf_callchain_entry) +
		sizeof(__u64) * (sysctl_perf_event_max_stack +
				 sysctl_perf_event_max_contexts_per_stack));
}