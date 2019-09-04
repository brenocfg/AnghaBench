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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_tracer_options (struct trace_array*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static void update_tracer_options(struct trace_array *tr)
{
	mutex_lock(&trace_types_lock);
	__update_tracer_options(tr);
	mutex_unlock(&trace_types_lock);
}