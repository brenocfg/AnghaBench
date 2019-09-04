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
struct uprobe_cpu_buffer {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct uprobe_cpu_buffer* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  uprobe_cpu_buffer ; 

__attribute__((used)) static struct uprobe_cpu_buffer *uprobe_buffer_get(void)
{
	struct uprobe_cpu_buffer *ucb;
	int cpu;

	cpu = raw_smp_processor_id();
	ucb = per_cpu_ptr(uprobe_cpu_buffer, cpu);

	/*
	 * Use per-cpu buffers for fastest access, but we might migrate
	 * so the mutex makes sure we have sole access to it.
	 */
	mutex_lock(&ucb->mutex);

	return ucb;
}