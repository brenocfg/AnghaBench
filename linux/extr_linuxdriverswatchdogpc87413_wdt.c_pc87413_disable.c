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
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  pc87413_disable_sw_wd_tren () ; 
 int /*<<< orphan*/  pc87413_disable_sw_wd_trg () ; 
 int /*<<< orphan*/  pc87413_programm_wdto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc87413_swc_bank3 () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pc87413_disable(void)
{
	spin_lock(&io_lock);

	pc87413_swc_bank3();
	pc87413_disable_sw_wd_tren();
	pc87413_disable_sw_wd_trg();
	pc87413_programm_wdto(0);

	spin_unlock(&io_lock);
}