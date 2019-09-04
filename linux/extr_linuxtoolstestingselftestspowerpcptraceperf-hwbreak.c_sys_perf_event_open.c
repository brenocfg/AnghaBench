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
struct perf_event_attr {int size; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_perf_event_open ; 
 int syscall (int /*<<< orphan*/ ,struct perf_event_attr*,int /*<<< orphan*/ ,int,int,unsigned long) ; 

__attribute__((used)) static inline int sys_perf_event_open(struct perf_event_attr *attr, pid_t pid,
				      int cpu, int group_fd,
				      unsigned long flags)
{
	attr->size = sizeof(*attr);
	return syscall(__NR_perf_event_open, attr, pid, cpu, group_fd, flags);
}