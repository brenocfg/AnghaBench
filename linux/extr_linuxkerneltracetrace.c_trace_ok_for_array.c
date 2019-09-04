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
struct tracer {scalar_t__ allow_instances; } ;
struct trace_array {int flags; } ;

/* Variables and functions */
 int TRACE_ARRAY_FL_GLOBAL ; 

__attribute__((used)) static bool
trace_ok_for_array(struct tracer *t, struct trace_array *tr)
{
	return (tr->flags & TRACE_ARRAY_FL_GLOBAL) || t->allow_instances;
}