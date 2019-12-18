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
struct symbol {int /*<<< orphan*/  annotate2; } ;
struct report {scalar_t__ symbol_ipc; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; struct symbol* sym; } ;
struct hist_entry {TYPE_1__ ms; int /*<<< orphan*/  hists; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__default_options ; 
 struct evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__annotate2 (struct symbol*,int /*<<< orphan*/ ,struct evsel*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hists__resort_cb(struct hist_entry *he, void *arg)
{
	struct report *rep = arg;
	struct symbol *sym = he->ms.sym;

	if (rep->symbol_ipc && sym && !sym->annotate2) {
		struct evsel *evsel = hists_to_evsel(he->hists);

		symbol__annotate2(sym, he->ms.map, evsel,
				  &annotation__default_options, NULL);
	}

	return 0;
}