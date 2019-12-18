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
struct map_symbol {TYPE_3__* sym; TYPE_2__* map; } ;
struct evsel {int dummy; } ;
struct annotation_options {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {TYPE_1__* dso; } ;
struct TYPE_4__ {char* long_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  perf_evsel__group_desc (struct evsel*,char*,int) ; 
 scalar_t__ perf_evsel__is_group_event (struct evsel*) ; 
 char* perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  symbol__annotate_fprintf2 (TYPE_3__*,int /*<<< orphan*/ *,struct annotation_options*) ; 

int map_symbol__annotation_dump(struct map_symbol *ms, struct evsel *evsel,
				struct annotation_options *opts)
{
	const char *ev_name = perf_evsel__name(evsel);
	char buf[1024];
	char *filename;
	int err = -1;
	FILE *fp;

	if (asprintf(&filename, "%s.annotation", ms->sym->name) < 0)
		return -1;

	fp = fopen(filename, "w");
	if (fp == NULL)
		goto out_free_filename;

	if (perf_evsel__is_group_event(evsel)) {
		perf_evsel__group_desc(evsel, buf, sizeof(buf));
		ev_name = buf;
	}

	fprintf(fp, "%s() %s\nEvent: %s\n\n",
		ms->sym->name, ms->map->dso->long_name, ev_name);
	symbol__annotate_fprintf2(ms->sym, fp, opts);

	fclose(fp);
	err = 0;
out_free_filename:
	free(filename);
	return err;
}