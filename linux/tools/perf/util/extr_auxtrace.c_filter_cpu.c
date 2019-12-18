#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_session {TYPE_1__* itrace_synth_opts; } ;
struct TYPE_2__ {unsigned long* cpu_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static bool filter_cpu(struct perf_session *session, int cpu)
{
	unsigned long *cpu_bitmap = session->itrace_synth_opts->cpu_bitmap;

	return cpu_bitmap && cpu != -1 && !test_bit(cpu, cpu_bitmap);
}