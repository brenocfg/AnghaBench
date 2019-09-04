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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_cpu (struct seq_file*,int) ; 
 int /*<<< orphan*/  sched_debug_header (struct seq_file*) ; 

__attribute__((used)) static int sched_debug_show(struct seq_file *m, void *v)
{
	int cpu = (unsigned long)(v - 2);

	if (cpu != -1)
		print_cpu(m, cpu);
	else
		sched_debug_header(m);

	return 0;
}