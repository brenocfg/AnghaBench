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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_2__ phydm; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phydm_get_version ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl_priv*) ; 

__attribute__((used)) static
u32 halbtc_get_phydm_version(void *btc_context)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (rtlpriv->phydm.ops)
		return rtlpriv->phydm.ops->phydm_get_version(rtlpriv);

	return 0;
}