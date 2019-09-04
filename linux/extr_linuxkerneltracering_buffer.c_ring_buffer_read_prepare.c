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
struct ring_buffer_per_cpu {int /*<<< orphan*/  record_disabled; } ;
struct ring_buffer_iter {struct ring_buffer_per_cpu* cpu_buffer; } ;
struct ring_buffer {int /*<<< orphan*/  resize_disabled; struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 struct ring_buffer_iter* kmalloc (int,int /*<<< orphan*/ ) ; 

struct ring_buffer_iter *
ring_buffer_read_prepare(struct ring_buffer *buffer, int cpu, gfp_t flags)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct ring_buffer_iter *iter;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return NULL;

	iter = kmalloc(sizeof(*iter), flags);
	if (!iter)
		return NULL;

	cpu_buffer = buffer->buffers[cpu];

	iter->cpu_buffer = cpu_buffer;

	atomic_inc(&buffer->resize_disabled);
	atomic_inc(&cpu_buffer->record_disabled);

	return iter;
}