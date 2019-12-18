#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct report {double min_percent; int /*<<< orphan*/  queue_size; } ;
struct TYPE_4__ {double min_percent; } ;
struct TYPE_3__ {void* cumulate_callchain; void* event_group; } ;

/* Variables and functions */
 TYPE_2__ callchain_param ; 
 int /*<<< orphan*/  default_sort_order ; 
 void* perf_config_bool (char const*,char const*) ; 
 int perf_config_u64 (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 double strtof (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int report__config(const char *var, const char *value, void *cb)
{
	struct report *rep = cb;

	if (!strcmp(var, "report.group")) {
		symbol_conf.event_group = perf_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "report.percent-limit")) {
		double pcnt = strtof(value, NULL);

		rep->min_percent = pcnt;
		callchain_param.min_percent = pcnt;
		return 0;
	}
	if (!strcmp(var, "report.children")) {
		symbol_conf.cumulate_callchain = perf_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "report.queue-size"))
		return perf_config_u64(&rep->queue_size, var, value);

	if (!strcmp(var, "report.sort_order")) {
		default_sort_order = strdup(value);
		return 0;
	}

	return 0;
}