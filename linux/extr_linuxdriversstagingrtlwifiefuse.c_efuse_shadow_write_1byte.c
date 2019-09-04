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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct rtl_efuse {int /*<<< orphan*/ ** efuse_map; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_MODIFY_MAP ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void efuse_shadow_write_1byte(struct ieee80211_hw *hw,
				     u16 offset, u8 value)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset] = value;
}