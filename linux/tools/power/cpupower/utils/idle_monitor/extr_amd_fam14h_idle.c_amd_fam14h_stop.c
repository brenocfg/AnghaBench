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
struct timespec {int dummy; } ;

/* Variables and functions */
 int AMD_FAM14H_STATE_NUM ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int OVERFLOW_MS ; 
 int /*<<< orphan*/ * amd_fam14h_cstates ; 
 int /*<<< orphan*/  amd_fam14h_disable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int cpu_count ; 
 struct timespec dbg_time ; 
 void* dbg_timediff ; 
 int /*<<< orphan*/  dprint (char*,void*) ; 
 int /*<<< orphan*/  print_overflow_err (unsigned int,int) ; 
 struct timespec start_time ; 
 int timediff ; 
 void* timespec_diff_us (struct timespec,struct timespec) ; 

__attribute__((used)) static int amd_fam14h_stop(void)
{
	int num, cpu;
	struct timespec end_time;

	clock_gettime(CLOCK_REALTIME, &end_time);

	for (num = 0; num < AMD_FAM14H_STATE_NUM; num++) {
		for (cpu = 0; cpu < cpu_count; cpu++)
			amd_fam14h_disable(&amd_fam14h_cstates[num], cpu);
	}
#ifdef DEBUG
	clock_gettime(CLOCK_REALTIME, &dbg_time);
	dbg_timediff = timespec_diff_us(end_time, dbg_time);
	dprint("Disabling counters took: %lu ns\n", dbg_timediff);
#endif
	timediff = timespec_diff_us(start_time, end_time);
	if (timediff / 1000 > OVERFLOW_MS)
		print_overflow_err((unsigned int)timediff / 1000000,
				   OVERFLOW_MS / 1000);

	return 0;
}