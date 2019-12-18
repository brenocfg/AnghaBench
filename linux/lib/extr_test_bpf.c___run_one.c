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
typedef  scalar_t__ u64 ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int BPF_PROG_RUN (struct bpf_prog const*,void const*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int __run_one(const struct bpf_prog *fp, const void *data,
		     int runs, u64 *duration)
{
	u64 start, finish;
	int ret = 0, i;

	preempt_disable();
	start = ktime_get_ns();

	for (i = 0; i < runs; i++)
		ret = BPF_PROG_RUN(fp, data);

	finish = ktime_get_ns();
	preempt_enable();

	*duration = finish - start;
	do_div(*duration, runs);

	return ret;
}