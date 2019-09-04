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
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct perf_sample {int dummy; } ;
struct perf_evsel {int /*<<< orphan*/  idx; TYPE_1__* evlist; } ;
struct map {int dummy; } ;
struct annotated_source {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __symbol__inc_addr_samples (struct symbol*,struct map*,struct annotated_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_sample*) ; 
 struct annotated_source* symbol__hists (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int symbol__inc_addr_samples(struct symbol *sym, struct map *map,
				    struct perf_evsel *evsel, u64 addr,
				    struct perf_sample *sample)
{
	struct annotated_source *src;

	if (sym == NULL)
		return 0;
	src = symbol__hists(sym, evsel->evlist->nr_entries);
	if (src == NULL)
		return -ENOMEM;
	return __symbol__inc_addr_samples(sym, map, src, evsel->idx, addr, sample);
}