#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int dummy; } ;
struct probe_trace_point {int /*<<< orphan*/  offset; int /*<<< orphan*/  symbol; scalar_t__ module; int /*<<< orphan*/  address; scalar_t__ retprobe; } ;
struct probe_trace_event {int nargs; int /*<<< orphan*/ * args; scalar_t__ uprobes; int /*<<< orphan*/  event; int /*<<< orphan*/  group; struct probe_trace_point point; } ;

/* Variables and functions */
 int strbuf_addf (struct strbuf*,char*,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ synthesize_probe_trace_arg (int /*<<< orphan*/ *,struct strbuf*) ; 
 int synthesize_uprobe_trace_def (struct probe_trace_event*,struct strbuf*) ; 

char *synthesize_probe_trace_command(struct probe_trace_event *tev)
{
	struct probe_trace_point *tp = &tev->point;
	struct strbuf buf;
	char *ret = NULL;
	int i, err;

	/* Uprobes must have tp->module */
	if (tev->uprobes && !tp->module)
		return NULL;

	if (strbuf_init(&buf, 32) < 0)
		return NULL;

	if (strbuf_addf(&buf, "%c:%s/%s ", tp->retprobe ? 'r' : 'p',
			tev->group, tev->event) < 0)
		goto error;
	/*
	 * If tp->address == 0, then this point must be a
	 * absolute address uprobe.
	 * try_to_find_absolute_address() should have made
	 * tp->symbol to "0x0".
	 */
	if (tev->uprobes && !tp->address) {
		if (!tp->symbol || strcmp(tp->symbol, "0x0"))
			goto error;
	}

	/* Use the tp->address for uprobes */
	if (tev->uprobes) {
		err = synthesize_uprobe_trace_def(tev, &buf);
	} else if (!strncmp(tp->symbol, "0x", 2)) {
		/* Absolute address. See try_to_find_absolute_address() */
		err = strbuf_addf(&buf, "%s%s0x%lx", tp->module ?: "",
				  tp->module ? ":" : "", tp->address);
	} else {
		err = strbuf_addf(&buf, "%s%s%s+%lu", tp->module ?: "",
				tp->module ? ":" : "", tp->symbol, tp->offset);
	}

	if (err)
		goto error;

	for (i = 0; i < tev->nargs; i++)
		if (synthesize_probe_trace_arg(&tev->args[i], &buf) < 0)
			goto error;

	ret = strbuf_detach(&buf, NULL);
error:
	strbuf_release(&buf);
	return ret;
}