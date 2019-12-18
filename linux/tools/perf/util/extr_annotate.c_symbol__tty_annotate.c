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
struct symbol {int dummy; } ;
struct rb_root {int dummy; } ;
struct map {struct dso* dso; } ;
struct evsel {int dummy; } ;
struct dso {int /*<<< orphan*/  long_name; } ;
struct annotation_options {int /*<<< orphan*/  full_path; scalar_t__ print_lines; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct rb_root RB_ROOT ; 
 int /*<<< orphan*/  annotated_source__purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_summary (struct rb_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcline_full_filename ; 
 scalar_t__ symbol__annotate (struct symbol*,struct map*,struct evsel*,int /*<<< orphan*/ ,struct annotation_options*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__annotate_printf (struct symbol*,struct map*,struct evsel*,struct annotation_options*) ; 
 TYPE_1__* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__calc_lines (struct symbol*,struct map*,struct rb_root*,struct annotation_options*) ; 
 int /*<<< orphan*/  symbol__calc_percent (struct symbol*,struct evsel*) ; 

int symbol__tty_annotate(struct symbol *sym, struct map *map,
			 struct evsel *evsel,
			 struct annotation_options *opts)
{
	struct dso *dso = map->dso;
	struct rb_root source_line = RB_ROOT;

	if (symbol__annotate(sym, map, evsel, 0, opts, NULL) < 0)
		return -1;

	symbol__calc_percent(sym, evsel);

	if (opts->print_lines) {
		srcline_full_filename = opts->full_path;
		symbol__calc_lines(sym, map, &source_line, opts);
		print_summary(&source_line, dso->long_name);
	}

	symbol__annotate_printf(sym, map, evsel, opts);

	annotated_source__purge(symbol__annotation(sym)->src);

	return 0;
}