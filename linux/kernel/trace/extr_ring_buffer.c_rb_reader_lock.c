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
struct ring_buffer_per_cpu {int /*<<< orphan*/  record_disabled; int /*<<< orphan*/  reader_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_nmi () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ raw_spin_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool rb_reader_lock(struct ring_buffer_per_cpu *cpu_buffer)
{
	if (likely(!in_nmi())) {
		raw_spin_lock(&cpu_buffer->reader_lock);
		return true;
	}

	/*
	 * If an NMI die dumps out the content of the ring buffer
	 * trylock must be used to prevent a deadlock if the NMI
	 * preempted a task that holds the ring buffer locks. If
	 * we get the lock then all is fine, if not, then continue
	 * to do the read, but this can corrupt the ring buffer,
	 * so it must be permanently disabled from future writes.
	 * Reading from NMI is a oneshot deal.
	 */
	if (raw_spin_trylock(&cpu_buffer->reader_lock))
		return true;

	/* Continue without locking, but disable the ring buffer */
	atomic_inc(&cpu_buffer->record_disabled);
	return false;
}