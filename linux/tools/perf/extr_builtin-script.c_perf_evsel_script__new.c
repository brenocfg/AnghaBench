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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
struct perf_data {TYPE_1__ file; } ;
struct evsel_script {int /*<<< orphan*/  filename; int /*<<< orphan*/ * fp; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct evsel_script*) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 struct evsel_script* zalloc (int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct evsel_script *perf_evsel_script__new(struct evsel *evsel,
							struct perf_data *data)
{
	struct evsel_script *es = zalloc(sizeof(*es));

	if (es != NULL) {
		if (asprintf(&es->filename, "%s.%s.dump", data->file.path, perf_evsel__name(evsel)) < 0)
			goto out_free;
		es->fp = fopen(es->filename, "w");
		if (es->fp == NULL)
			goto out_free_filename;
	}

	return es;
out_free_filename:
	zfree(&es->filename);
out_free:
	free(es);
	return NULL;
}