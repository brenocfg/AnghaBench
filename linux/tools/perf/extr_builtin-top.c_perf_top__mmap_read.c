#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int overwrite; } ;
struct perf_top {struct evlist* evlist; TYPE_1__ record_opts; } ;
struct TYPE_4__ {int nr_mmaps; } ;
struct evlist {TYPE_2__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BKW_MMAP_DATA_PENDING ; 
 int /*<<< orphan*/  BKW_MMAP_EMPTY ; 
 int /*<<< orphan*/  BKW_MMAP_RUNNING ; 
 int /*<<< orphan*/  perf_evlist__toggle_bkw_mmap (struct evlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_top__mmap_read_idx (struct perf_top*,int) ; 

__attribute__((used)) static void perf_top__mmap_read(struct perf_top *top)
{
	bool overwrite = top->record_opts.overwrite;
	struct evlist *evlist = top->evlist;
	int i;

	if (overwrite)
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_DATA_PENDING);

	for (i = 0; i < top->evlist->core.nr_mmaps; i++)
		perf_top__mmap_read_idx(top, i);

	if (overwrite) {
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_EMPTY);
		perf_evlist__toggle_bkw_mmap(evlist, BKW_MMAP_RUNNING);
	}
}