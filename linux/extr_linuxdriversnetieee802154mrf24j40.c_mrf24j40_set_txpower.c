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
typedef  int u8 ;
struct mrf24j40 {int /*<<< orphan*/  regmap_long; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_RFCON3 ; 
 int TXPWRL_0 ; 
 int TXPWRL_10 ; 
 int TXPWRL_20 ; 
 int TXPWRL_30 ; 
 int TXPWRL_MASK ; 
 int TXPWRL_SHIFT ; 
 int TXPWRS_0 ; 
 int TXPWRS_0_5 ; 
 int TXPWRS_1_2 ; 
 int TXPWRS_1_9 ; 
 int TXPWRS_2_8 ; 
 int TXPWRS_3_7 ; 
 int TXPWRS_4_9 ; 
 int TXPWRS_6_3 ; 
 int TXPWRS_MASK ; 
 int TXPWRS_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mrf24j40_set_txpower(struct ieee802154_hw *hw, s32 mbm)
{
	struct mrf24j40 *devrec = hw->priv;
	s32 small_scale;
	u8 val;

	if (0 >= mbm && mbm > -1000) {
		val = TXPWRL_0 << TXPWRL_SHIFT;
		small_scale = mbm;
	} else if (-1000 >= mbm && mbm > -2000) {
		val = TXPWRL_10 << TXPWRL_SHIFT;
		small_scale = mbm + 1000;
	} else if (-2000 >= mbm && mbm > -3000) {
		val = TXPWRL_20 << TXPWRL_SHIFT;
		small_scale = mbm + 2000;
	} else if (-3000 >= mbm && mbm > -4000) {
		val = TXPWRL_30 << TXPWRL_SHIFT;
		small_scale = mbm + 3000;
	} else {
		return -EINVAL;
	}

	switch (small_scale) {
	case 0:
		val |= (TXPWRS_0 << TXPWRS_SHIFT);
		break;
	case -50:
		val |= (TXPWRS_0_5 << TXPWRS_SHIFT);
		break;
	case -120:
		val |= (TXPWRS_1_2 << TXPWRS_SHIFT);
		break;
	case -190:
		val |= (TXPWRS_1_9 << TXPWRS_SHIFT);
		break;
	case -280:
		val |= (TXPWRS_2_8 << TXPWRS_SHIFT);
		break;
	case -370:
		val |= (TXPWRS_3_7 << TXPWRS_SHIFT);
		break;
	case -490:
		val |= (TXPWRS_4_9 << TXPWRS_SHIFT);
		break;
	case -630:
		val |= (TXPWRS_6_3 << TXPWRS_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(devrec->regmap_long, REG_RFCON3,
				  TXPWRL_MASK | TXPWRS_MASK, val);
}