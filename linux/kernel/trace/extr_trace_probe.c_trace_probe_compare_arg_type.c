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
struct trace_probe {int nr_args; TYPE_1__* args; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int trace_probe_compare_arg_type(struct trace_probe *a, struct trace_probe *b)
{
	int i;

	/* In case of more arguments */
	if (a->nr_args < b->nr_args)
		return a->nr_args + 1;
	if (a->nr_args > b->nr_args)
		return b->nr_args + 1;

	for (i = 0; i < a->nr_args; i++) {
		if ((b->nr_args <= i) ||
		    ((a->args[i].type != b->args[i].type) ||
		     (a->args[i].count != b->args[i].count) ||
		     strcmp(a->args[i].name, b->args[i].name)))
			return i + 1;
	}

	return 0;
}