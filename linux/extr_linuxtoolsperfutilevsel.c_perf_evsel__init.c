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
struct perf_event_attr {int /*<<< orphan*/  sample_type; } ;
struct perf_evsel {int idx; int tracking; char* unit; double scale; int bpf_fd; int cmdline_group_boundary; int collect_stat; int /*<<< orphan*/ * pmu_name; int /*<<< orphan*/ * metric_events; int /*<<< orphan*/ * metric_name; int /*<<< orphan*/ * metric_expr; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  config_terms; int /*<<< orphan*/  node; int /*<<< orphan*/ * evlist; struct perf_evsel* leader; struct perf_event_attr attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct perf_evsel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __perf_evsel__sample_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__calc_id_pos (struct perf_evsel*) ; 
 TYPE_1__ perf_evsel__object ; 
 int /*<<< orphan*/  stub1 (struct perf_evsel*) ; 

void perf_evsel__init(struct perf_evsel *evsel,
		      struct perf_event_attr *attr, int idx)
{
	evsel->idx	   = idx;
	evsel->tracking	   = !idx;
	evsel->attr	   = *attr;
	evsel->leader	   = evsel;
	evsel->unit	   = "";
	evsel->scale	   = 1.0;
	evsel->evlist	   = NULL;
	evsel->bpf_fd	   = -1;
	INIT_LIST_HEAD(&evsel->node);
	INIT_LIST_HEAD(&evsel->config_terms);
	perf_evsel__object.init(evsel);
	evsel->sample_size = __perf_evsel__sample_size(attr->sample_type);
	perf_evsel__calc_id_pos(evsel);
	evsel->cmdline_group_boundary = false;
	evsel->metric_expr   = NULL;
	evsel->metric_name   = NULL;
	evsel->metric_events = NULL;
	evsel->collect_stat  = false;
	evsel->pmu_name      = NULL;
}