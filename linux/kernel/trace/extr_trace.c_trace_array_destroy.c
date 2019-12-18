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
 int EINVAL ; 
 int __remove_instance (struct trace_array*) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_types_lock ; 

int trace_array_destroy(struct trace_array *tr)
{
	int ret;

	if (!tr)
		return -EINVAL;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	ret = __remove_instance(tr);

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	return ret;
}