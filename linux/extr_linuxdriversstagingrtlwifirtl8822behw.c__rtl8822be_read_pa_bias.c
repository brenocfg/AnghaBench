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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct rtl_halmac_ops* ops; } ;
struct rtl_priv {TYPE_1__ halmac; } ;
struct rtl_phydm_params {int efuse0x3d7; int efuse0x3d8; } ;
struct rtl_halmac_ops {scalar_t__ (* halmac_read_physical_efuse_map ) (struct rtl_priv*,void**,int /*<<< orphan*/ ) ;scalar_t__ (* halmac_get_physical_efuse_size ) (struct rtl_priv*,int /*<<< orphan*/ *) ;} ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ stub1 (struct rtl_priv*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct rtl_priv*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl8822be_read_pa_bias(struct ieee80211_hw *hw,
				    struct rtl_phydm_params *params)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_halmac_ops *halmac_ops = rtlpriv->halmac.ops;
	u32 size;
	u8 *map = NULL;

	/* fill default values */
	params->efuse0x3d7 = 0xFF;
	params->efuse0x3d8 = 0xFF;

	if (halmac_ops->halmac_get_physical_efuse_size(rtlpriv, &size))
		goto err;

	map = kmalloc(size, GFP_KERNEL);
	if (!map)
		goto err;

	if (halmac_ops->halmac_read_physical_efuse_map(rtlpriv, map, size))
		goto err;

	params->efuse0x3d7 = map[0x3d7];
	params->efuse0x3d8 = map[0x3d8];

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "efuse0x3d7 = 0x%2x, efuse0x3d8 = 0x%2x\n",
		 params->efuse0x3d7, params->efuse0x3d8);

err:
	kfree(map);
}