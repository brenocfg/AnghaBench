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
struct event_ring_info {int /*<<< orphan*/  mem; } ;
typedef  enum bpf_perf_event_ret { ____Placeholder_bpf_perf_event_ret } bpf_perf_event_ret ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int MMAP_PAGE_CNT ; 
 int bpf_perf_event_read_simple (int /*<<< orphan*/ ,int,int,void**,size_t*,int /*<<< orphan*/ ,struct event_ring_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_page_size () ; 
 int /*<<< orphan*/  print_bpf_output ; 
 int /*<<< orphan*/  stderr ; 
 int stop ; 

__attribute__((used)) static void
perf_event_read(struct event_ring_info *ring, void **buf, size_t *buf_len)
{
	enum bpf_perf_event_ret ret;

	ret = bpf_perf_event_read_simple(ring->mem,
					 MMAP_PAGE_CNT * get_page_size(),
					 get_page_size(), buf, buf_len,
					 print_bpf_output, ring);
	if (ret != LIBBPF_PERF_EVENT_CONT) {
		fprintf(stderr, "perf read loop failed with %d\n", ret);
		stop = true;
	}
}