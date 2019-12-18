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
struct perf_cpu_buf {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  base; } ;
struct perf_buffer {int /*<<< orphan*/  page_size; int /*<<< orphan*/  mmap_size; } ;
typedef  enum bpf_perf_event_ret { ____Placeholder_bpf_perf_event_ret } bpf_perf_event_ret ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int bpf_perf_event_read_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_cpu_buf*) ; 
 int /*<<< orphan*/  perf_buffer__process_record ; 

__attribute__((used)) static int perf_buffer__process_records(struct perf_buffer *pb,
					struct perf_cpu_buf *cpu_buf)
{
	enum bpf_perf_event_ret ret;

	ret = bpf_perf_event_read_simple(cpu_buf->base, pb->mmap_size,
					 pb->page_size, &cpu_buf->buf,
					 &cpu_buf->buf_size,
					 perf_buffer__process_record, cpu_buf);
	if (ret != LIBBPF_PERF_EVENT_CONT)
		return ret;
	return 0;
}