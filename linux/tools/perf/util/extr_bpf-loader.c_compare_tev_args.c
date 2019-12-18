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
struct probe_trace_event {int nargs; struct probe_trace_arg* args; } ;
struct probe_trace_arg_ref {int offset; struct probe_trace_arg_ref* next; } ;
struct probe_trace_arg {struct probe_trace_arg_ref* ref; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_tev_args(const void *ptev1, const void *ptev2)
{
	int i, ret;
	const struct probe_trace_event *tev1 =
		*(const struct probe_trace_event **)ptev1;
	const struct probe_trace_event *tev2 =
		*(const struct probe_trace_event **)ptev2;

	ret = tev2->nargs - tev1->nargs;
	if (ret)
		return ret;

	for (i = 0; i < tev1->nargs; i++) {
		struct probe_trace_arg *arg1, *arg2;
		struct probe_trace_arg_ref *ref1, *ref2;

		arg1 = &tev1->args[i];
		arg2 = &tev2->args[i];

		ret = strcmp(arg1->value, arg2->value);
		if (ret)
			return ret;

		ref1 = arg1->ref;
		ref2 = arg2->ref;

		while (ref1 && ref2) {
			ret = ref2->offset - ref1->offset;
			if (ret)
				return ret;

			ref1 = ref1->next;
			ref2 = ref2->next;
		}

		if (ref1 || ref2)
			return ref2 ? 1 : -1;
	}

	return 0;
}