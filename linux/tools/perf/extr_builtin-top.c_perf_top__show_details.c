#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct symbol {char* name; } ;
struct TYPE_9__ {int min_pcnt; } ;
struct perf_top {TYPE_3__* sym_evsel; scalar_t__ zero; TYPE_2__* evlist; TYPE_4__ annotation_opts; struct hist_entry* sym_filter_entry; } ;
struct TYPE_6__ {int /*<<< orphan*/  map; struct symbol* sym; } ;
struct hist_entry {TYPE_1__ ms; int /*<<< orphan*/  hists; } ;
struct evsel {int dummy; } ;
struct annotation {int /*<<< orphan*/  lock; int /*<<< orphan*/ * src; } ;
struct TYPE_8__ {int /*<<< orphan*/  idx; } ;
struct TYPE_7__ {scalar_t__ enabled; } ;

/* Variables and functions */
 struct evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 char* perf_evsel__name (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__annotate_decay_histogram (struct symbol*,int /*<<< orphan*/ ) ; 
 int symbol__annotate_printf (struct symbol*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  symbol__annotate_zero_histogram (struct symbol*,int /*<<< orphan*/ ) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__calc_percent (struct symbol*,struct evsel*) ; 

__attribute__((used)) static void perf_top__show_details(struct perf_top *top)
{
	struct hist_entry *he = top->sym_filter_entry;
	struct evsel *evsel;
	struct annotation *notes;
	struct symbol *symbol;
	int more;

	if (!he)
		return;

	evsel = hists_to_evsel(he->hists);

	symbol = he->ms.sym;
	notes = symbol__annotation(symbol);

	pthread_mutex_lock(&notes->lock);

	symbol__calc_percent(symbol, evsel);

	if (notes->src == NULL)
		goto out_unlock;

	printf("Showing %s for %s\n", perf_evsel__name(top->sym_evsel), symbol->name);
	printf("  Events  Pcnt (>=%d%%)\n", top->annotation_opts.min_pcnt);

	more = symbol__annotate_printf(symbol, he->ms.map, top->sym_evsel, &top->annotation_opts);

	if (top->evlist->enabled) {
		if (top->zero)
			symbol__annotate_zero_histogram(symbol, top->sym_evsel->idx);
		else
			symbol__annotate_decay_histogram(symbol, top->sym_evsel->idx);
	}
	if (more != 0)
		printf("%d lines not displayed, maybe increase display entries [e]\n", more);
out_unlock:
	pthread_mutex_unlock(&notes->lock);
}