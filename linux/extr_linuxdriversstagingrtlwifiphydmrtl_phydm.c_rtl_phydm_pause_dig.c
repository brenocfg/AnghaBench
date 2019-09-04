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
 int /*<<< orphan*/  PHYDM_PAUSE ; 
 int /*<<< orphan*/  PHYDM_PAUSE_LEVEL_0 ; 
 int /*<<< orphan*/  PHYDM_RESUME ; 
 int /*<<< orphan*/  odm_pause_dig (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_pause_dig(struct rtl_priv *rtlpriv, bool pause)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	if (pause)
		odm_pause_dig(dm, PHYDM_PAUSE, PHYDM_PAUSE_LEVEL_0, 0x1e);
	else /* resume */
		odm_pause_dig(dm, PHYDM_RESUME, PHYDM_PAUSE_LEVEL_0, 0xff);

	return true;
}