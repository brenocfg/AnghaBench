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
struct trace_event_call {struct module* mod; int /*<<< orphan*/  list; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int event_init (struct trace_event_call*) ; 
 int /*<<< orphan*/  ftrace_events ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__register_event(struct trace_event_call *call, struct module *mod)
{
	int ret;

	ret = event_init(call);
	if (ret < 0)
		return ret;

	list_add(&call->list, &ftrace_events);
	call->mod = mod;

	return 0;
}