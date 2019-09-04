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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pm_status ; 
 int /*<<< orphan*/  ps3_read_pm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 ps3_get_and_clear_pm_interrupts(u32 cpu)
{
	return ps3_read_pm(cpu, pm_status);
}