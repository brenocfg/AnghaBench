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
struct perf_event_attr {int precise_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void perf_event_attr__set_max_precise_ip(struct perf_event_attr *attr)
{
	attr->precise_ip = 3;

	while (attr->precise_ip != 0) {
		int fd = sys_perf_event_open(attr, 0, -1, -1, 0);
		if (fd != -1) {
			close(fd);
			break;
		}
		--attr->precise_ip;
	}
}