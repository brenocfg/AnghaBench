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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RING_BUFFER_ALL_CPUS ; 
 int __tracing_resize_ring_buffer (struct trace_array*,unsigned long,int) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int /*<<< orphan*/  tracing_buffer_mask ; 

__attribute__((used)) static ssize_t tracing_resize_ring_buffer(struct trace_array *tr,
					  unsigned long size, int cpu_id)
{
	int ret = size;

	mutex_lock(&trace_types_lock);

	if (cpu_id != RING_BUFFER_ALL_CPUS) {
		/* make sure, this cpu is enabled in the mask */
		if (!cpumask_test_cpu(cpu_id, tracing_buffer_mask)) {
			ret = -EINVAL;
			goto out;
		}
	}

	ret = __tracing_resize_ring_buffer(tr, size, cpu_id);
	if (ret < 0)
		ret = -ENOMEM;

out:
	mutex_unlock(&trace_types_lock);

	return ret;
}