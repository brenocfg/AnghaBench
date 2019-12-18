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
struct perf_cpu_buf {scalar_t__ fd; struct perf_cpu_buf* buf; int /*<<< orphan*/  cpu; scalar_t__ base; } ;
struct perf_buffer {scalar_t__ page_size; scalar_t__ mmap_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_DISABLE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct perf_cpu_buf*) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_buffer__free_cpu_buf(struct perf_buffer *pb,
				      struct perf_cpu_buf *cpu_buf)
{
	if (!cpu_buf)
		return;
	if (cpu_buf->base &&
	    munmap(cpu_buf->base, pb->mmap_size + pb->page_size))
		pr_warning("failed to munmap cpu_buf #%d\n", cpu_buf->cpu);
	if (cpu_buf->fd >= 0) {
		ioctl(cpu_buf->fd, PERF_EVENT_IOC_DISABLE, 0);
		close(cpu_buf->fd);
	}
	free(cpu_buf->buf);
	free(cpu_buf);
}