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
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int crystalcap; } ;
struct phy_dm_struct {scalar_t__ adapter; } ;

/* Variables and functions */
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 

__attribute__((used)) static u8 odm_get_default_crytaltal_cap(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 crystal_cap = 0x20;

	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);

	crystal_cap = rtlefuse->crystalcap;

	crystal_cap = crystal_cap & 0x3f;

	return crystal_cap;
}