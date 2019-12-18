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
 int /*<<< orphan*/  create_cpu_entry (int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stress_cpumap(void)
{
	/* Changing qsize will cause kernel to free and alloc a new
	 * bpf_cpu_map_entry, with an associated/complicated tear-down
	 * procedure.
	 */
	create_cpu_entry(1,  1024, 0, false);
	create_cpu_entry(1,     8, 0, false);
	create_cpu_entry(1, 16000, 0, false);
}