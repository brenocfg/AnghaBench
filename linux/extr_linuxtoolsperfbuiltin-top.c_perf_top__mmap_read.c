#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int overwrite; } ;
struct perf_top {scalar_t__ delay_secs; struct perf_evlist* evlist; TYPE_1__ record_opts; } ;
struct perf_evlist {int nr_mmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BKW_MMAP_DATA_PENDING ; 
 int /*<<< orphan*/  BKW_MMAP_EMPTY ; 
 int /*<<< orphan*/  BKW_MMAP_RUNNING ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  perf_evlist__toggle_bkw_mmap (struct perf_evlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_top__mmap_read_idx (struct perf_top*,int) ; 
 unsigned long long rdclock () ; 
 int /*<<< orphan*/  ui__warning (char*) ; 

__attribute__((used)) static void perf_top__mmap_read(struct perf_top *top)
{
	bool overwrite = top->record_opts.overwrite;
	struct perf_evlist *evlist = top->evlist;
	unsigned long long start, end;
	int i;

	start = rdclock();
	if (overwrite)
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_DATA_PENDING);

	for (i = 0; i < top->evlist->nr_mmaps; i++)
		perf_top__mmap_read_idx(top, i);

	if (overwrite) {
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_EMPTY);
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_RUNNING);
	}
	end = rdclock();

	if ((end - start) > (unsigned long long)top->delay_secs * NSEC_PER_SEC)
		ui__warning("Too slow to read ring buffer.\n"
			    "Please try increasing the period (-c) or\n"
			    "decreasing the freq (-F) or\n"
			    "limiting the number of CPUs (-C)\n");
}