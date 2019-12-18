#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int /*<<< orphan*/  name; } ;
struct perf_top {TYPE_2__* sym_filter_entry; } ;
struct perf_sample {int dummy; } ;
struct TYPE_8__ {TYPE_5__* map; struct symbol* sym; } ;
struct hist_entry {TYPE_4__* hists; TYPE_3__ ms; } ;
struct evsel {int dummy; } ;
struct annotation {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  erange_warned; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {struct symbol* sym; } ;
struct TYPE_7__ {TYPE_1__ ms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int hist_entry__inc_addr_samples (struct hist_entry*,struct perf_sample*,struct evsel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  ui__warn_map_erange (TYPE_5__*,struct symbol*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ use_browser ; 

__attribute__((used)) static void perf_top__record_precise_ip(struct perf_top *top,
					struct hist_entry *he,
					struct perf_sample *sample,
					struct evsel *evsel, u64 ip)
{
	struct annotation *notes;
	struct symbol *sym = he->ms.sym;
	int err = 0;

	if (sym == NULL || (use_browser == 0 &&
			    (top->sym_filter_entry == NULL ||
			     top->sym_filter_entry->ms.sym != sym)))
		return;

	notes = symbol__annotation(sym);

	if (pthread_mutex_trylock(&notes->lock))
		return;

	err = hist_entry__inc_addr_samples(he, sample, evsel, ip);

	pthread_mutex_unlock(&notes->lock);

	if (unlikely(err)) {
		/*
		 * This function is now called with he->hists->lock held.
		 * Release it before going to sleep.
		 */
		pthread_mutex_unlock(&he->hists->lock);

		if (err == -ERANGE && !he->ms.map->erange_warned)
			ui__warn_map_erange(he->ms.map, sym, ip);
		else if (err == -ENOMEM) {
			pr_err("Not enough memory for annotating '%s' symbol!\n",
			       sym->name);
			sleep(1);
		}

		pthread_mutex_lock(&he->hists->lock);
	}
}