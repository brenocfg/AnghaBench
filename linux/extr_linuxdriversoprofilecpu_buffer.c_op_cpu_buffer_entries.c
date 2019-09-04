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

/* Variables and functions */
 int /*<<< orphan*/  op_ring_buffer ; 
 unsigned long ring_buffer_entries_cpu (int /*<<< orphan*/ ,int) ; 

unsigned long op_cpu_buffer_entries(int cpu)
{
	return ring_buffer_entries_cpu(op_ring_buffer, cpu);
}