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
struct symbol {int dummy; } ;
struct perf_evsel {int nr_members; } ;
struct map {int dummy; } ;
struct arch {int dummy; } ;
struct annotation_options {int dummy; } ;
struct annotation_line {int dummy; } ;
struct annotation {int nr_events; int /*<<< orphan*/ * offsets; struct annotation_options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__compute_ipc (struct annotation*,size_t) ; 
 int /*<<< orphan*/  annotation__init_column_widths (struct annotation*,struct symbol*) ; 
 int /*<<< orphan*/  annotation__mark_jump_targets (struct annotation*,struct symbol*) ; 
 int /*<<< orphan*/  annotation__set_offsets (struct annotation*,size_t) ; 
 int /*<<< orphan*/  annotation__update_column_widths (struct annotation*) ; 
 scalar_t__ perf_evsel__is_group_event (struct perf_evsel*) ; 
 int symbol__annotate (struct symbol*,struct map*,struct perf_evsel*,int /*<<< orphan*/ ,struct annotation_options*,struct arch**) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__calc_percent (struct symbol*,struct perf_evsel*) ; 
 size_t symbol__size (struct symbol*) ; 
 int /*<<< orphan*/ * zalloc (size_t) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int symbol__annotate2(struct symbol *sym, struct map *map, struct perf_evsel *evsel,
		      struct annotation_options *options, struct arch **parch)
{
	struct annotation *notes = symbol__annotation(sym);
	size_t size = symbol__size(sym);
	int nr_pcnt = 1, err;

	notes->offsets = zalloc(size * sizeof(struct annotation_line *));
	if (notes->offsets == NULL)
		return -1;

	if (perf_evsel__is_group_event(evsel))
		nr_pcnt = evsel->nr_members;

	err = symbol__annotate(sym, map, evsel, 0, options, parch);
	if (err)
		goto out_free_offsets;

	notes->options = options;

	symbol__calc_percent(sym, evsel);

	annotation__set_offsets(notes, size);
	annotation__mark_jump_targets(notes, sym);
	annotation__compute_ipc(notes, size);
	annotation__init_column_widths(notes, sym);
	notes->nr_events = nr_pcnt;

	annotation__update_column_widths(notes);

	return 0;

out_free_offsets:
	zfree(&notes->offsets);
	return -1;
}