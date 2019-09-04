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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int /*<<< orphan*/  hw; } ;
struct phy_dm_struct {scalar_t__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_get_bbreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 odm_get_bb_reg(struct phy_dm_struct *dm, u32 reg_addr, u32 bit_mask)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	return rtl_get_bbreg(rtlpriv->hw, reg_addr, bit_mask);
}