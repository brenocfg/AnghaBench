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
struct evsel_priv {struct bt_ctf_event_class* event_class; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {struct evsel_priv* priv; TYPE_2__ core; } ;
struct ctf_writer {int /*<<< orphan*/  stream_class; } ;
struct bt_ctf_event_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_TRACEPOINT ; 
 int add_bpf_output_types (struct ctf_writer*,struct bt_ctf_event_class*) ; 
 int add_generic_types (struct ctf_writer*,struct evsel*,struct bt_ctf_event_class*) ; 
 int add_tracepoint_types (struct ctf_writer*,struct evsel*,struct bt_ctf_event_class*) ; 
 struct bt_ctf_event_class* bt_ctf_event_class_create (char const*) ; 
 int /*<<< orphan*/  bt_ctf_event_class_put (struct bt_ctf_event_class*) ; 
 int bt_ctf_stream_class_add_event_class (int /*<<< orphan*/ ,struct bt_ctf_event_class*) ; 
 struct evsel_priv* malloc (int) ; 
 scalar_t__ perf_evsel__is_bpf_output (struct evsel*) ; 
 char* perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  pr (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int add_event(struct ctf_writer *cw, struct evsel *evsel)
{
	struct bt_ctf_event_class *event_class;
	struct evsel_priv *priv;
	const char *name = perf_evsel__name(evsel);
	int ret;

	pr("Adding event '%s' (type %d)\n", name, evsel->core.attr.type);

	event_class = bt_ctf_event_class_create(name);
	if (!event_class)
		return -1;

	ret = add_generic_types(cw, evsel, event_class);
	if (ret)
		goto err;

	if (evsel->core.attr.type == PERF_TYPE_TRACEPOINT) {
		ret = add_tracepoint_types(cw, evsel, event_class);
		if (ret)
			goto err;
	}

	if (perf_evsel__is_bpf_output(evsel)) {
		ret = add_bpf_output_types(cw, event_class);
		if (ret)
			goto err;
	}

	ret = bt_ctf_stream_class_add_event_class(cw->stream_class, event_class);
	if (ret) {
		pr("Failed to add event class into stream.\n");
		goto err;
	}

	priv = malloc(sizeof(*priv));
	if (!priv)
		goto err;

	priv->event_class = event_class;
	evsel->priv       = priv;
	return 0;

err:
	bt_ctf_event_class_put(event_class);
	pr_err("Failed to add event '%s'.\n", name);
	return -1;
}