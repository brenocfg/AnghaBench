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
struct trace_export {struct trace_export* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (struct trace_export*,struct trace_export*) ; 

__attribute__((used)) static inline int
rm_trace_export(struct trace_export **list, struct trace_export *export)
{
	struct trace_export **p;

	for (p = list; *p != NULL; p = &(*p)->next)
		if (*p == export)
			break;

	if (*p != export)
		return -1;

	rcu_assign_pointer(*p, (*p)->next);

	return 0;
}