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
struct trace_export {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_exports_disable () ; 
 int rm_trace_export (struct trace_export**,struct trace_export*) ; 

__attribute__((used)) static inline int
rm_ftrace_export(struct trace_export **list, struct trace_export *export)
{
	int ret;

	ret = rm_trace_export(list, export);
	if (*list == NULL)
		ftrace_exports_disable();

	return ret;
}