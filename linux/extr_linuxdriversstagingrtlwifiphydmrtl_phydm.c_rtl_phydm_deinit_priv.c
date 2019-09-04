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
struct TYPE_2__ {int /*<<< orphan*/ * internal; } ;
struct rtl_priv {TYPE_1__ phydm; } ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  odm_cancel_all_timers (struct phy_dm_struct*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static int rtl_phydm_deinit_priv(struct rtl_priv *rtlpriv)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	odm_cancel_all_timers(dm);

	kfree(rtlpriv->phydm.internal);
	rtlpriv->phydm.internal = NULL;

	return 0;
}