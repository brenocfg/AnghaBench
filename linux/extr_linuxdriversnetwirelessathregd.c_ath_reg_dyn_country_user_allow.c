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
struct ath_regulatory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ATH_REG_DYNAMIC_USER_REG_HINTS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_country_user_possible (struct ath_regulatory*) ; 

__attribute__((used)) static bool ath_reg_dyn_country_user_allow(struct ath_regulatory *reg)
{
	if (!IS_ENABLED(CONFIG_ATH_REG_DYNAMIC_USER_REG_HINTS))
		return false;
	if (!dynamic_country_user_possible(reg))
		return false;
	return true;
}