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
struct symbol {char* name; } ;
struct rb_root {int dummy; } ;
struct map {struct dso* dso; } ;
struct hists {int dummy; } ;
struct evsel {int dummy; } ;
struct dso {char* long_name; } ;
struct annotation_options {int /*<<< orphan*/  percent_type; int /*<<< orphan*/  full_path; scalar_t__ print_lines; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct rb_root RB_ROOT ; 
 int /*<<< orphan*/  annotated_source__purge (int /*<<< orphan*/ ) ; 
 struct hists* evsel__hists (struct evsel*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  hists__scnprintf_title (struct hists*,char*,int) ; 
 char* percent_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_summary (struct rb_root*,char*) ; 
 int /*<<< orphan*/  srcline_full_filename ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ symbol__annotate2 (struct symbol*,struct map*,struct evsel*,struct annotation_options*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__annotate_fprintf2 (struct symbol*,int /*<<< orphan*/ ,struct annotation_options*) ; 
 TYPE_1__* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__calc_lines (struct symbol*,struct map*,struct rb_root*,struct annotation_options*) ; 

int symbol__tty_annotate2(struct symbol *sym, struct map *map,
			  struct evsel *evsel,
			  struct annotation_options *opts)
{
	struct dso *dso = map->dso;
	struct rb_root source_line = RB_ROOT;
	struct hists *hists = evsel__hists(evsel);
	char buf[1024];

	if (symbol__annotate2(sym, map, evsel, opts, NULL) < 0)
		return -1;

	if (opts->print_lines) {
		srcline_full_filename = opts->full_path;
		symbol__calc_lines(sym, map, &source_line, opts);
		print_summary(&source_line, dso->long_name);
	}

	hists__scnprintf_title(hists, buf, sizeof(buf));
	fprintf(stdout, "%s, [percent: %s]\n%s() %s\n",
		buf, percent_type_str(opts->percent_type), sym->name, dso->long_name);
	symbol__annotate_fprintf2(sym, stdout, opts);

	annotated_source__purge(symbol__annotation(sym)->src);

	return 0;
}