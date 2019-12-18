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
struct perf_event_attr {int dummy; } ;

/* Variables and functions */
 int __event (int,void*,struct perf_event_attr*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ test_function ; 
 int /*<<< orphan*/  the_var ; 

__attribute__((used)) static int detect_cnt(bool is_x)
{
	struct perf_event_attr attr;
	void *addr = is_x ? (void *)test_function : (void *)&the_var;
	int fd[100], cnt = 0, i;

	while (1) {
		if (cnt == 100) {
			pr_debug("way too many debug registers, fix the test\n");
			return 0;
		}
		fd[cnt] = __event(is_x, addr, &attr);

		if (fd[cnt] < 0)
			break;
		cnt++;
	}

	for (i = 0; i < cnt; i++)
		close(fd[i]);

	return cnt;
}