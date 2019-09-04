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
typedef  long long __u64 ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int LIBBPF_PERF_EVENT_DONE ; 
 int LIBBPF_PERF_EVENT_ERROR ; 
 long long MAX_CNT ; 
 int /*<<< orphan*/  printf (char*,long long,...) ; 
 long long start_time ; 
 long long time_get_ns () ; 

__attribute__((used)) static int print_bpf_output(void *data, int size)
{
	static __u64 cnt;
	struct {
		__u64 pid;
		__u64 cookie;
	} *e = data;

	if (e->cookie != 0x12345678) {
		printf("BUG pid %llx cookie %llx sized %d\n",
		       e->pid, e->cookie, size);
		return LIBBPF_PERF_EVENT_ERROR;
	}

	cnt++;

	if (cnt == MAX_CNT) {
		printf("recv %lld events per sec\n",
		       MAX_CNT * 1000000000ll / (time_get_ns() - start_time));
		return LIBBPF_PERF_EVENT_DONE;
	}

	return LIBBPF_PERF_EVENT_CONT;
}