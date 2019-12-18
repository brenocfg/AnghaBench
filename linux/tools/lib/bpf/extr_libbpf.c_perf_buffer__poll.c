#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_cpu_buf {int dummy; } ;
struct perf_buffer {TYPE_2__* events; int /*<<< orphan*/  cpu_cnt; int /*<<< orphan*/  epoll_fd; } ;
struct TYPE_3__ {struct perf_cpu_buf* ptr; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int epoll_wait (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int perf_buffer__process_records (struct perf_buffer*,struct perf_cpu_buf*) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

int perf_buffer__poll(struct perf_buffer *pb, int timeout_ms)
{
	int i, cnt, err;

	cnt = epoll_wait(pb->epoll_fd, pb->events, pb->cpu_cnt, timeout_ms);
	for (i = 0; i < cnt; i++) {
		struct perf_cpu_buf *cpu_buf = pb->events[i].data.ptr;

		err = perf_buffer__process_records(pb, cpu_buf);
		if (err) {
			pr_warning("error while processing records: %d\n", err);
			return err;
		}
	}
	return cnt < 0 ? -errno : cnt;
}