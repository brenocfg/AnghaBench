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
struct perf_buffer {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int perf_buffer__poll (struct perf_buffer*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void tcp_notifier_poller(struct perf_buffer *pb)
{
	int err;

	while (1) {
		err = perf_buffer__poll(pb, 100);
		if (err < 0 && err != -EINTR) {
			printf("failed perf_buffer__poll: %d\n", err);
			return;
		}
	}
}