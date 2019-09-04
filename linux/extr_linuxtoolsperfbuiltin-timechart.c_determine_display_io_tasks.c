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
typedef  scalar_t__ u64 ;
struct timechart {scalar_t__ last_time; struct per_pid* all_data; } ;
struct per_pidcomm {int display; scalar_t__ total_bytes; scalar_t__ end_time; struct per_pidcomm* next; } ;
struct per_pid {scalar_t__ end_time; struct per_pid* next; struct per_pidcomm* all; } ;

/* Variables and functions */

__attribute__((used)) static int determine_display_io_tasks(struct timechart *timechart, u64 threshold)
{
	struct per_pid *p;
	struct per_pidcomm *c;
	int count = 0;

	p = timechart->all_data;
	while (p) {
		/* no exit marker, task kept running to the end */
		if (p->end_time == 0)
			p->end_time = timechart->last_time;

		c = p->all;

		while (c) {
			c->display = 0;

			if (c->total_bytes >= threshold) {
				c->display = 1;
				count++;
			}

			if (c->end_time == 0)
				c->end_time = timechart->last_time;

			c = c->next;
		}
		p = p->next;
	}
	return count;
}