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
 int /*<<< orphan*/  PERF_EVENT_IOC_MODIFY_ATTRIBUTES ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct perf_event_attr*) ; 
 int /*<<< orphan*/  the_var ; 
 int wp_event (void*,struct perf_event_attr*) ; 

__attribute__((used)) static int detect_ioctl(void)
{
	struct perf_event_attr attr;
	int fd, ret = 1;

	fd = wp_event((void *) &the_var, &attr);
	if (fd > 0) {
		ret = ioctl(fd, PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &attr);
		close(fd);
	}

	return ret ? 0 : 1;
}