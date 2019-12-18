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
struct tep_format_field {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;
struct evsel {int /*<<< orphan*/  tp_format; TYPE_2__ core; } ;
struct evlist {int dummy; } ;
struct TYPE_6__ {int raw_trace; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 int __dynamic_dimension__add (struct evsel*,struct tep_format_field*,int,int) ; 
 int add_all_dynamic_fields (struct evlist*,int,int) ; 
 int add_all_matching_fields (struct evlist*,char*,int,int) ; 
 int add_evsel_fields (struct evsel*,int,int) ; 
 struct evsel* find_evsel (struct evlist*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ parse_field_name (char*,char**,char**,char**) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 TYPE_3__ symbol_conf ; 
 struct tep_format_field* tep_find_any_field (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int add_dynamic_entry(struct evlist *evlist, const char *tok,
			     int level)
{
	char *str, *event_name, *field_name, *opt_name;
	struct evsel *evsel;
	struct tep_format_field *field;
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

	if (evsel->core.attr.type != PERF_TYPE_TRACEPOINT) {
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