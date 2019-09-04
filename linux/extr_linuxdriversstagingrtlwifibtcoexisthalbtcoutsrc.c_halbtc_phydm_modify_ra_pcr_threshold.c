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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {struct rtl_phydm_ops* ops; } ;
struct rtl_priv {TYPE_1__ phydm; } ;
struct rtl_phydm_ops {int /*<<< orphan*/  (* phydm_modify_ra_pcr_threshold ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void halbtc_phydm_modify_ra_pcr_threshold(void *btc_context,
					  u8 ra_offset_direction,
					  u8 ra_threshold_offset)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_phydm_ops *phydm_ops = rtlpriv->phydm.ops;

	if (phydm_ops)
		phydm_ops->phydm_modify_ra_pcr_threshold(rtlpriv,
							 ra_offset_direction,
							 ra_threshold_offset);
}