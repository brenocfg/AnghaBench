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

/* Variables and functions */
 int /*<<< orphan*/  LC_NUMERIC ; 
 struct stats_record* alloc_stats_record () ; 
 int /*<<< orphan*/  free_stats_record (struct stats_record*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stats_collect (struct stats_record*) ; 
 int /*<<< orphan*/  stats_print (struct stats_record*,struct stats_record*,char*) ; 
 int /*<<< orphan*/  stress_cpumap () ; 
 int /*<<< orphan*/  swap (struct stats_record**,struct stats_record**) ; 

__attribute__((used)) static void stats_poll(int interval, bool use_separators, char *prog_name,
		       bool stress_mode)
{
	struct stats_record *record, *prev;

	record = alloc_stats_record();
	prev   = alloc_stats_record();
	stats_collect(record);

	/* Trick to pretty printf with thousands separators use %' */
	if (use_separators)
		setlocale(LC_NUMERIC, "en_US");

	while (1) {
		swap(&prev, &record);
		stats_collect(record);
		stats_print(record, prev, prog_name);
		sleep(interval);
		if (stress_mode)
			stress_cpumap();
	}

	free_stats_record(record);
	free_stats_record(prev);
}