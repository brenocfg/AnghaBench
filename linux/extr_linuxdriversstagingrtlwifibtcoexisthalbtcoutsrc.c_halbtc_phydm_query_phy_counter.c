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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct rtl_phydm_ops* ops; } ;
struct rtl_priv {TYPE_1__ phydm; } ;
struct rtl_phydm_ops {int /*<<< orphan*/  (* phydm_query_counter ) (struct rtl_priv*,char const*) ;} ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl_priv*,char const*) ; 

__attribute__((used)) static
u32 halbtc_phydm_query_phy_counter(void *btc_context, const char *info_type)
{
	/* info_type may be strings below:
	 * PHYDM_INFO_FA_OFDM, PHYDM_INFO_FA_CCK, PHYDM_INFO_CCA_OFDM,
	 * PHYDM_INFO_CCA_CCK
	 * IQK_TOTAL, IQK_OK, IQK_FAIL
	 */

	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_phydm_ops *phydm_ops = rtlpriv->phydm.ops;

	if (phydm_ops)
		return phydm_ops->phydm_query_counter(rtlpriv, info_type);

	return 0;
}