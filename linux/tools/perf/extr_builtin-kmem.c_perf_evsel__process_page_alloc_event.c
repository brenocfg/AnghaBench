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
typedef  void* u64 ;
struct perf_sample {int dummy; } ;
struct page_stat {unsigned int order; unsigned int gfp_flags; unsigned int migrate_type; int /*<<< orphan*/  alloc_bytes; int /*<<< orphan*/  nr_alloc; void* callsite; void* page; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* find_callsite (struct evsel*,struct perf_sample*) ; 
 unsigned int kmem_page_size ; 
 int /*<<< orphan*/  live_page ; 
 int /*<<< orphan*/  nr_page_allocs ; 
 int /*<<< orphan*/  nr_page_fails ; 
 int /*<<< orphan*/ ** order_stats ; 
 struct page_stat* page_stat__findnew_alloc (struct page_stat*) ; 
 struct page_stat* page_stat__findnew_caller (struct page_stat*) ; 
 struct page_stat* page_stat__findnew_page (struct page_stat*) ; 
 scalar_t__ parse_gfp_flags (struct evsel*,struct perf_sample*,unsigned int) ; 
 void* perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  total_page_alloc_bytes ; 
 int /*<<< orphan*/  total_page_fail_bytes ; 
 scalar_t__ use_pfn ; 
 int /*<<< orphan*/  valid_page (void*) ; 

__attribute__((used)) static int perf_evsel__process_page_alloc_event(struct evsel *evsel,
						struct perf_sample *sample)
{
	u64 page;
	unsigned int order = perf_evsel__intval(evsel, sample, "order");
	unsigned int gfp_flags = perf_evsel__intval(evsel, sample, "gfp_flags");
	unsigned int migrate_type = perf_evsel__intval(evsel, sample,
						       "migratetype");
	u64 bytes = kmem_page_size << order;
	u64 callsite;
	struct page_stat *pstat;
	struct page_stat this = {
		.order = order,
		.gfp_flags = gfp_flags,
		.migrate_type = migrate_type,
	};

	if (use_pfn)
		page = perf_evsel__intval(evsel, sample, "pfn");
	else
		page = perf_evsel__intval(evsel, sample, "page");

	nr_page_allocs++;
	total_page_alloc_bytes += bytes;

	if (!valid_page(page)) {
		nr_page_fails++;
		total_page_fail_bytes += bytes;

		return 0;
	}

	if (parse_gfp_flags(evsel, sample, gfp_flags) < 0)
		return -1;

	callsite = find_callsite(evsel, sample);

	/*
	 * This is to find the current page (with correct gfp flags and
	 * migrate type) at free event.
	 */
	this.page = page;
	pstat = page_stat__findnew_page(&this);
	if (pstat == NULL)
		return -ENOMEM;

	pstat->nr_alloc++;
	pstat->alloc_bytes += bytes;
	pstat->callsite = callsite;

	if (!live_page) {
		pstat = page_stat__findnew_alloc(&this);
		if (pstat == NULL)
			return -ENOMEM;

		pstat->nr_alloc++;
		pstat->alloc_bytes += bytes;
		pstat->callsite = callsite;
	}

	this.callsite = callsite;
	pstat = page_stat__findnew_caller(&this);
	if (pstat == NULL)
		return -ENOMEM;

	pstat->nr_alloc++;
	pstat->alloc_bytes += bytes;

	order_stats[order][migrate_type]++;

	return 0;
}