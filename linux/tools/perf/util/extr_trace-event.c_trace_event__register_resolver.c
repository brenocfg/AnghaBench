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
typedef  int /*<<< orphan*/  tep_func_resolver_t ;
struct machine {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pevent; } ;

/* Variables and functions */
 int tep_set_function_resolver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct machine*) ; 
 TYPE_1__ tevent ; 
 int /*<<< orphan*/  tevent_initialized ; 
 scalar_t__ trace_event__init2 () ; 

int trace_event__register_resolver(struct machine *machine,
				   tep_func_resolver_t *func)
{
	if (!tevent_initialized && trace_event__init2())
		return -1;

	return tep_set_function_resolver(tevent.pevent, func, machine);
}