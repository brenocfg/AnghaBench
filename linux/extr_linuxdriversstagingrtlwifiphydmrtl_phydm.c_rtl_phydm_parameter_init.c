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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int /*<<< orphan*/  ODM_POST_SETTING ; 
 int /*<<< orphan*/  ODM_PRE_SETTING ; 
 int config_phydm_parameter_init (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_parameter_init(struct rtl_priv *rtlpriv, bool post)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		return config_phydm_parameter_init(dm, post ? ODM_POST_SETTING :
							      ODM_PRE_SETTING);

	return false;
}