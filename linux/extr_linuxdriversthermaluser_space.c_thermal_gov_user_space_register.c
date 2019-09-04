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
 int thermal_register_governor (int /*<<< orphan*/ *) ; 

int thermal_gov_user_space_register(void)
{
	return thermal_register_governor(&thermal_gov_user_space);
}