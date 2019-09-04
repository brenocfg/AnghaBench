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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE1 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE2 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE3 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE4 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE5 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE6 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE7 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE8 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE9 ; 
 int /*<<< orphan*/  AR9170_PHY_REG_POWER_TX_RATE_MAX ; 
 int /*<<< orphan*/  carl9170_regwrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

__attribute__((used)) static int carl9170_init_power_cal(struct ar9170 *ar)
{
	carl9170_regwrite_begin(ar);

	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE_MAX, 0x7f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE1, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE2, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE3, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE4, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE5, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE6, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE7, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE8, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE9, 0x3f3f3f3f);

	carl9170_regwrite_finish();
	return carl9170_regwrite_result();
}