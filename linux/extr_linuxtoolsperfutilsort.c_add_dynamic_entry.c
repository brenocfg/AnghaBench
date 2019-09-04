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
struct TYPE_3__ {scalar_t__ type; } ;
struct perf_evsel {int /*<<< orphan*/  tp_format; TYPE_1__ attr; } ;
struct perf_evlist {int dummy; } ;
struct format_field {int dummy; } ;
struct TYPE_4__ {int raw_trace; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 int __dynamic_dimension__add (struct perf_evsel*,struct format_field*,int,int) ; 
 int add_all_dynamic_fields (struct perf_evlist*,int,int) ; 
 int add_all_matching_fields (struct perf_evlist*,char*,int,int) ; 
 int add_evsel_fields (struct perf_evsel*,int,int) ; 
 struct perf_evsel* find_evsel (struct perf_evlist*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ parse_field_name (char*,char**,char**,char**) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 TYPE_2__ symbol_conf ; 
 struct format_field* tep_find_any_field (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int add_dynamic_entry(struct perf_evlist *evlist, const char *tok,
			     int level)
{
	char *str, *event_name, *field_name, *opt_name;
	struct perf_evsel *evsel;
	struct format_field *field;
	bool raw_trace = symbol_conf.raw_trace;
	int ret = 0;

	if (evlist == NULL)
		return -ENOENT;

	str = strdup(tok);
	if (str == NULL)
		return -ENOMEM;

	if (parse_field_name(str, &event_name, &field_name, &opt_name) < 0) {
		ret = -EINVAL;
		goto out;
	}

	if (opt_name) {
		if (strcmp(opt_name, "raw")) {
			pr_debug("unsupported field option %s\n", opt_name);
			ret = -EINVAL;
			goto out;
		}
		raw_trace = true;
	}

	if (!strcmp(field_name, "trace_fields")) {
		ret = add_all_dynamic_fields(evlist, raw_trace, level);
		goto out;
	}

	if (event_name == NULL) {
		ret = add_all_matching_fields(evlist, field_name, raw_trace, level);
		goto out;
	}

	evsel = find_evsel(evlist, event_name);
	if (evsel == NULL) {
		pr_debug("Cannot find event: %s\n", event_name);
		ret = -ENOENT;
		goto out;
	}

	if (evsel->attr.type != PERF_TYPE_TRACEPOINT) {
		pr_debug("%s is not a tracepoint event\n", event_name);
		ret = -EINVAL;
		goto out;
	}

	if (!strcmp(field_name, "*")) {
		ret = add_evsel_fields(evsel, raw_trace, level);
	} else {
		field = tep_find_any_field(evsel->tp_format, field_name);
		if (field == NULL) {
			pr_debug("Cannot find event field for %s.%s\n",
				 event_name, field_name);
			return -ENOENT;
		}

		ret = __dynamic_dimension__add(evsel, field, raw_trace, level);
	}

out:
	free(str);
	return ret;
}