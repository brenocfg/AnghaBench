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
 int /*<<< orphan*/  cpuhp_remove_state_nocalls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_online ; 

__attribute__((used)) static void oprofile_hrtimer_shutdown(void)
{
	cpuhp_remove_state_nocalls(hp_online);
}