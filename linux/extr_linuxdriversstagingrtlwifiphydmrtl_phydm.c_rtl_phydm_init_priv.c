#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  internal; } ;
struct rtl_priv {TYPE_1__ phydm; } ;
struct rtl_phydm_params {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_ic_type { ____Placeholder_odm_ic_type } odm_ic_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  _rtl_phydm_init_com_info (struct rtl_priv*,int,struct rtl_phydm_params*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_init_all_timers (struct phy_dm_struct*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static int rtl_phydm_init_priv(struct rtl_priv *rtlpriv,
			       struct rtl_phydm_params *params)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	enum odm_ic_type ic;

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		ic = ODM_RTL8822B;
	else
		return 0;

	rtlpriv->phydm.internal =
		kzalloc(sizeof(struct phy_dm_struct), GFP_KERNEL);

	_rtl_phydm_init_com_info(rtlpriv, ic, params);

	odm_init_all_timers(dm);

	return 1;
}