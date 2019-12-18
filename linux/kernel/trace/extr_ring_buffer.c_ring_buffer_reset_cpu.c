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
struct ring_buffer_per_cpu {int /*<<< orphan*/  record_disabled; int /*<<< orphan*/  reader_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  committing; } ;
struct ring_buffer {int /*<<< orphan*/  resize_disabled; int /*<<< orphan*/  cpumask; struct ring_buffer_per_cpu** buffers; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rb_reset_cpu (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void ring_buffer_reset_cpu(struct ring_buffer *buffer, int cpu)
{
	struct ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	unsigned long flags;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return;

	atomic_inc(&buffer->resize_disabled);
	atomic_inc(&cpu_buffer->record_disabled);

	/* Make sure all commits have finished */
	synchronize_rcu();

	raw_spin_lock_irqsave(&cpu_buffer->reader_lock, flags);

	if (RB_WARN_ON(cpu_buffer, local_read(&cpu_buffer->committing)))
		goto out;

	arch_spin_lock(&cpu_buffer->lock);

	rb_reset_cpu(cpu_buffer);

	arch_spin_unlock(&cpu_buffer->lock);

 out:
	raw_spin_unlock_irqrestore(&cpu_buffer->reader_lock, flags);

	atomic_dec(&cpu_buffer->record_disabled);
	atomic_dec(&buffer->resize_disabled);
}