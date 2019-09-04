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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (scalar_t__) ; 
 int get_winver () ; 

void os_sleep_ms(uint32_t duration)
{
	/* windows 8+ appears to have decreased sleep precision */
	if (get_winver() >= 0x0602 && duration > 0)
		duration--;

	Sleep(duration);
}