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
struct stats_record {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 struct stats_record* alloc_stats_record () ; 
 int /*<<< orphan*/  free_stats_record (struct stats_record*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stats_collect (struct stats_record*) ; 
 int /*<<< orphan*/  stats_print (struct stats_record*,struct stats_record*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (struct stats_record**,struct stats_record**) ; 

__attribute__((used)) static void stats_poll(int interval, int action, __u32 cfg_opt)
{
	struct stats_record *record, *prev;

	record = alloc_stats_record();
	prev   = alloc_stats_record();
	stats_collect(record);

	while (1) {
		swap(&prev, &record);
		stats_collect(record);
		stats_print(record, prev, action, cfg_opt);
		sleep(interval);
	}

	free_stats_record(record);
	free_stats_record(prev);
}