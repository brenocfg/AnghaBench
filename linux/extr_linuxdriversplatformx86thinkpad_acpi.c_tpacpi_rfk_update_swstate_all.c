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
 unsigned int TPACPI_RFK_SW_MAX ; 
 int /*<<< orphan*/  tpacpi_rfk_update_swstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tpacpi_rfkill_switches ; 

__attribute__((used)) static void tpacpi_rfk_update_swstate_all(void)
{
	unsigned int i;

	for (i = 0; i < TPACPI_RFK_SW_MAX; i++)
		tpacpi_rfk_update_swstate(tpacpi_rfkill_switches[i]);
}