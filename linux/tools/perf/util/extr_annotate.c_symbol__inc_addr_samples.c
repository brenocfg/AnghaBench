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
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct perf_sample {int dummy; } ;
struct map {int dummy; } ;
struct evsel {int /*<<< orphan*/  idx; TYPE_2__* evlist; } ;
struct annotated_source {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_entries; } ;
struct TYPE_4__ {TYPE_1__ core; } ;

/* Variables and functions */
 int __symbol__inc_addr_samples (struct symbol*,struct map*,struct annotated_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_sample*) ; 
 struct annotated_source* symbol__hists (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int symbol__inc_addr_samples(struct symbol *sym, struct map *map,
				    struct evsel *evsel, u64 addr,
				    struct perf_sample *sample)
{
	struct annotated_source *src;

	if (sym == NULL)
		return 0;
	src = symbol__hists(sym, evsel->evlist->core.nr_entries);
	return (src) ?  __symbol__inc_addr_samples(sym, map, src, evsel->idx,
						   addr, sample) : 0;
}