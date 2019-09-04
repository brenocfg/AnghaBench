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
typedef  size_t u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t IQK_ADDA_REG_NUM ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92ee_phy_path_adda_on(struct ieee80211_hw *hw, u32 *addareg,
				      bool is_patha_on, bool is2t)
{
	u32 i;

	for (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, 0x0fc01616);
}