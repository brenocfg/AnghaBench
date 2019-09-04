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
 int /*<<< orphan*/  thermal_gov_user_space ; 
 int /*<<< orphan*/  thermal_unregister_governor (int /*<<< orphan*/ *) ; 

void thermal_gov_user_space_unregister(void)
{
	thermal_unregister_governor(&thermal_gov_user_space);
}