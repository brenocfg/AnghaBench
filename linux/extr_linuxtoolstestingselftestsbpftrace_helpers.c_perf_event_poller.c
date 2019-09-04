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
typedef  int /*<<< orphan*/  perf_event_print_fn ;
typedef  enum bpf_perf_event_ret { ____Placeholder_bpf_perf_event_ret } bpf_perf_event_ret ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int /*<<< orphan*/  bpf_perf_event_print ; 
 int bpf_perf_event_read_simple (int /*<<< orphan*/ ,int,int,void**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  header ; 
 int page_cnt ; 
 int page_size ; 
 int /*<<< orphan*/  perf_event_poll (int) ; 

int perf_event_poller(int fd, perf_event_print_fn output_fn)
{
	enum bpf_perf_event_ret ret;
	void *buf = NULL;
	size_t len = 0;

	for (;;) {
		perf_event_poll(fd);
		ret = bpf_perf_event_read_simple(header, page_cnt * page_size,
						 page_size, &buf, &len,
						 bpf_perf_event_print,
						 output_fn);
		if (ret != LIBBPF_PERF_EVENT_CONT)
			break;
	}
	free(buf);

	return ret;
}