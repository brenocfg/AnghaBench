#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* threads; } ;
struct TYPE_3__ {unsigned int curr_cpu; } ;

/* Variables and functions */
 TYPE_2__* g ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int sched_getcpu () ; 

__attribute__((used)) static void update_curr_cpu(int task_nr, unsigned long bytes_worked)
{
	unsigned int cpu;

	cpu = sched_getcpu();

	g->threads[task_nr].curr_cpu = cpu;
	prctl(0, bytes_worked);
}