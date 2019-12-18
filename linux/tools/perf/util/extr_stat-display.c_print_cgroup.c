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
struct perf_stat_config {char* csv_sep; int /*<<< orphan*/  output; } ;
struct evsel {TYPE_1__* cgrp; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ nr_cgroups ; 

__attribute__((used)) static void print_cgroup(struct perf_stat_config *config, struct evsel *evsel)
{
	if (nr_cgroups) {
		const char *cgrp_name = evsel->cgrp ? evsel->cgrp->name  : "";
		fprintf(config->output, "%s%s", config->csv_sep, cgrp_name);
	}
}