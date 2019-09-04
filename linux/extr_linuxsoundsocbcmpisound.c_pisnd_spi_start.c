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
 int /*<<< orphan*/  TASK_PROCESS ; 
 int /*<<< orphan*/  pisnd_schedule_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printd (char*) ; 

__attribute__((used)) static void pisnd_spi_start(void)
{
	printd("schedule from spi_start\n");
	pisnd_schedule_process(TASK_PROCESS);
}