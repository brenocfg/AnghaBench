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
 int /*<<< orphan*/  cpu_stat_inject_cpu_frequency_event () ; 
 int /*<<< orphan*/  cpu_stat_inject_cpu_idle_event () ; 
 int /*<<< orphan*/  cpu_stat_print () ; 
 int /*<<< orphan*/  cpu_stat_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_fd ; 

__attribute__((used)) static void int_exit(int sig)
{
	cpu_stat_inject_cpu_idle_event();
	cpu_stat_inject_cpu_frequency_event();
	cpu_stat_update(map_fd[1], map_fd[2]);
	cpu_stat_print();
	exit(0);
}