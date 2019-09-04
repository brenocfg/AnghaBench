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
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PHY_ACT ; 
 int /*<<< orphan*/  AR5K_PHY_ACT_DISABLE ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath5k_hw_phy_disable(struct ath5k_hw *ah)
{
	/*Just a try M.F.*/
	ath5k_hw_reg_write(ah, AR5K_PHY_ACT_DISABLE, AR5K_PHY_ACT);

	return 0;
}