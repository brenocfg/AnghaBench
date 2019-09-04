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
struct strbuf {int dummy; } ;
struct probe_trace_event {int nargs; TYPE_2__* args; int /*<<< orphan*/  point; scalar_t__ group; scalar_t__ event; } ;
struct perf_probe_event {int nargs; TYPE_1__* args; int /*<<< orphan*/  point; int /*<<< orphan*/ * group; int /*<<< orphan*/ * event; } ;
struct perf_probe_arg {int dummy; } ;
struct TYPE_4__ {scalar_t__ name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  clear_perf_probe_event (struct perf_probe_event*) ; 
 int convert_to_perf_probe_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int strbuf_init (struct strbuf*,int) ; 
 void* strdup (scalar_t__) ; 
 int synthesize_probe_trace_arg (TYPE_2__*,struct strbuf*) ; 
 TYPE_1__* zalloc (int) ; 

__attribute__((used)) static int convert_to_perf_probe_event(struct probe_trace_event *tev,
			       struct perf_probe_event *pev, bool is_kprobe)
{
	struct strbuf buf = STRBUF_INIT;
	int i, ret;

	/* Convert event/group name */
	pev->event = strdup(tev->event);
	pev->group = strdup(tev->group);
	if (pev->event == NULL || pev->group == NULL)
		return -ENOMEM;

	/* Convert trace_point to probe_point */
	ret = convert_to_perf_probe_point(&tev->point, &pev->point, is_kprobe);
	if (ret < 0)
		return ret;

	/* Convert trace_arg to probe_arg */
	pev->nargs = tev->nargs;
	pev->args = zalloc(sizeof(struct perf_probe_arg) * pev->nargs);
	if (pev->args == NULL)
		return -ENOMEM;
	for (i = 0; i < tev->nargs && ret >= 0; i++) {
		if (tev->args[i].name)
			pev->args[i].name = strdup(tev->args[i].name);
		else {
			if ((ret = strbuf_init(&buf, 32)) < 0)
				goto error;
			ret = synthesize_probe_trace_arg(&tev->args[i], &buf);
			pev->args[i].name = strbuf_detach(&buf, NULL);
		}
		if (pev->args[i].name == NULL && ret >= 0)
			ret = -ENOMEM;
	}
error:
	if (ret < 0)
		clear_perf_probe_event(pev);

	return ret;
}