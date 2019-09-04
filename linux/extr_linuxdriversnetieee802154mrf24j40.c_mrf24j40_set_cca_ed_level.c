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
struct mrf24j40 {int /*<<< orphan*/  regmap_short; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_CCAEDTH ; 
 scalar_t__** mrf24j40_ed_levels_map ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mrf24j40_set_cca_ed_level(struct ieee802154_hw *hw, s32 mbm)
{
	struct mrf24j40 *devrec = hw->priv;
	int i;

	for (i = 0; i < ARRAY_SIZE(mrf24j40_ed_levels_map); i++) {
		if (mrf24j40_ed_levels_map[i][0] == mbm)
			return regmap_write(devrec->regmap_short, REG_CCAEDTH,
					    mrf24j40_ed_levels_map[i][1]);
	}

	return -EINVAL;
}