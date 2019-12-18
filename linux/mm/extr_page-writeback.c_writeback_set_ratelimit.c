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
struct wb_domain {unsigned long dirty_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  global_dirty_limits (unsigned long*,unsigned long*) ; 
 struct wb_domain global_wb_domain ; 
 int num_online_cpus () ; 
 int ratelimit_pages ; 

void writeback_set_ratelimit(void)
{
	struct wb_domain *dom = &global_wb_domain;
	unsigned long background_thresh;
	unsigned long dirty_thresh;

	global_dirty_limits(&background_thresh, &dirty_thresh);
	dom->dirty_limit = dirty_thresh;
	ratelimit_pages = dirty_thresh / (num_online_cpus() * 32);
	if (ratelimit_pages < 16)
		ratelimit_pages = 16;
}