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
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 TYPE_1__ cpu_stopper ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sched_set_stop_task (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_stop_create(unsigned int cpu)
{
	sched_set_stop_task(cpu, per_cpu(cpu_stopper.thread, cpu));
}