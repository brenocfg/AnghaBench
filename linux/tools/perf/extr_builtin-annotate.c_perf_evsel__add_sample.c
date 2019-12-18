#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int /*<<< orphan*/  branch_stack; } ;
struct perf_annotate {scalar_t__ has_br_stack; int /*<<< orphan*/ * sym_hist_filter; } ;
struct machine {int dummy; } ;
struct hists {int dummy; } ;
struct hist_entry {int dummy; } ;
struct evsel {int dummy; } ;
struct addr_location {int /*<<< orphan*/  addr; TYPE_1__* map; TYPE_2__* sym; } ;
struct TYPE_6__ {int /*<<< orphan*/  symbols; } ;
struct TYPE_5__ {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_3__* dso; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dso__reset_find_symbol_cache (TYPE_3__*) ; 
 struct hists* evsel__hists (struct evsel*) ; 
 scalar_t__ has_annotation (struct perf_annotate*) ; 
 int hist_entry__inc_addr_samples (struct hist_entry*,struct perf_sample*,struct evsel*,int /*<<< orphan*/ ) ; 
 struct hist_entry* hists__add_entry (struct hists*,struct addr_location*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct perf_sample*,int) ; 
 int /*<<< orphan*/  hists__inc_nr_samples (struct hists*,int) ; 
 int process_branch_callback (struct evsel*,struct perf_sample*,struct addr_location*,struct perf_annotate*,struct machine*) ; 
 int /*<<< orphan*/  process_branch_stack (int /*<<< orphan*/ ,struct addr_location*,struct perf_sample*) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__delete (TYPE_2__*) ; 

__attribute__((used)) static int perf_evsel__add_sample(struct evsel *evsel,
				  struct perf_sample *sample,
				  struct addr_location *al,
				  struct perf_annotate *ann,
				  struct machine *machine)
{
	struct hists *hists = evsel__hists(evsel);
	struct hist_entry *he;
	int ret;

	if ((!ann->has_br_stack || !has_annotation(ann)) &&
	    ann->sym_hist_filter != NULL &&
	    (al->sym == NULL ||
	     strcmp(ann->sym_hist_filter, al->sym->name) != 0)) {
		/* We're only interested in a symbol named sym_hist_filter */
		/*
		 * FIXME: why isn't this done in the symbol_filter when loading
		 * the DSO?
		 */
		if (al->sym != NULL) {
			rb_erase_cached(&al->sym->rb_node,
				 &al->map->dso->symbols);
			symbol__delete(al->sym);
			dso__reset_find_symbol_cache(al->map->dso);
		}
		return 0;
	}

	/*
	 * XXX filtered samples can still have branch entires pointing into our
	 * symbol and are missed.
	 */
	process_branch_stack(sample->branch_stack, al, sample);

	if (ann->has_br_stack && has_annotation(ann))
		return process_branch_callback(evsel, sample, al, ann, machine);

	he = hists__add_entry(hists, al, NULL, NULL, NULL, sample, true);
	if (he == NULL)
		return -ENOMEM;

	ret = hist_entry__inc_addr_samples(he, sample, evsel, al->addr);
	hists__inc_nr_samples(hists, true);
	return ret;
}