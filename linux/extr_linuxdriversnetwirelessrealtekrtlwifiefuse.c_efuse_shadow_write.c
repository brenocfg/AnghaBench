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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efuse_shadow_write_1byte (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  efuse_shadow_write_2byte (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efuse_shadow_write_4byte (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

void efuse_shadow_write(struct ieee80211_hw *hw, u8 type, u16 offset,
				u32 value)
{
	if (type == 1)
		efuse_shadow_write_1byte(hw, offset, (u8) value);
	else if (type == 2)
		efuse_shadow_write_2byte(hw, offset, (u16) value);
	else if (type == 4)
		efuse_shadow_write_4byte(hw, offset, value);

}