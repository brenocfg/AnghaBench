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
struct ring_buffer_per_cpu {int /*<<< orphan*/  reader_lock; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
rb_reader_unlock(struct ring_buffer_per_cpu *cpu_buffer, bool locked)
{
	if (likely(locked))
		raw_spin_unlock(&cpu_buffer->reader_lock);
	return;
}