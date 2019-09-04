#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int /*<<< orphan*/  hw; TYPE_2__* cfg; } ;
struct phy_dm_struct {scalar_t__ adapter; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fill_h2c_cmd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYDM_COMP_RA_DBG ; 
 int /*<<< orphan*/  phydm_trans_h2c_id (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void odm_fill_h2c_cmd(struct phy_dm_struct *dm, u8 phydm_h2c_id, u32 cmd_len,
		      u8 *cmd_buffer)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	u8 platform_h2c_id;

	platform_h2c_id = phydm_trans_h2c_id(dm, phydm_h2c_id);

	ODM_RT_TRACE(dm, PHYDM_COMP_RA_DBG,
		     "[H2C]  platform_h2c_id = ((0x%x))\n", platform_h2c_id);

	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->hw, platform_h2c_id, cmd_len,
					cmd_buffer);
}