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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_PROCESS ; 
 int /*<<< orphan*/  g_ledFlashDuration ; 
 int g_ledFlashDurationChanged ; 
 int /*<<< orphan*/  pisnd_schedule_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printd (char*) ; 

__attribute__((used)) static void pisnd_spi_flash_leds(uint8_t duration)
{
	g_ledFlashDuration = duration;
	g_ledFlashDurationChanged = true;
	printd("schedule from spi_flash_leds\n");
	pisnd_schedule_process(TASK_PROCESS);
}