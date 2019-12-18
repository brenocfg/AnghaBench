#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct perf_event_attr {int sample_type; int sample_period; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct evsel {int /*<<< orphan*/  name; TYPE_1__* tp_format; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct evsel* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  PERF_TYPE_TRACEPOINT ; 
 int PTR_ERR (TYPE_1__*) ; 
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  evsel__init (struct evsel*,struct perf_event_attr*,int) ; 
 int /*<<< orphan*/  free (struct evsel*) ; 
 TYPE_2__ perf_evsel__object ; 
 TYPE_1__* trace_event__tp_format (char const*,char const*) ; 
 struct evsel* zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

struct evsel *perf_evsel__newtp_idx(const char *sys, const char *name, int idx)
{
	struct evsel *evsel = zalloc(perf_evsel__object.size);
	int err = -ENOMEM;

	if (evsel == NULL) {
		goto out_err;
	} else {
		struct perf_event_attr attr = {
			.type	       = PERF_TYPE_TRACEPOINT,
			.sample_type   = (PERF_SAMPLE_RAW | PERF_SAMPLE_TIME |
					  PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD),
		};

		if (asprintf(&evsel->name, "%s:%s", sys, name) < 0)
			goto out_free;

		evsel->tp_format = trace_event__tp_format(sys, name);
		if (IS_ERR(evsel->tp_format)) {
			err = PTR_ERR(evsel->tp_format);
			goto out_free;
		}

		event_attr_init(&attr);
		attr.config = evsel->tp_format->id;
		attr.sample_period = 1;
		evsel__init(evsel, &attr, idx);
	}

	return evsel;

out_free:
	zfree(&evsel->name);
	free(evsel);
out_err:
	return ERR_PTR(err);
}