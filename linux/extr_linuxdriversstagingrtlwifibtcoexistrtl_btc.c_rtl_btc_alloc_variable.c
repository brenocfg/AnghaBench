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
struct wifi_only_cfg {int dummy; } ;
struct TYPE_2__ {void* btc_context; void* wifi_only_context; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_btc_alloc_variable(struct rtl_priv *rtlpriv, bool wifi_only)
{
	if (wifi_only)
		rtlpriv->btcoexist.wifi_only_context =
			kzalloc(sizeof(struct wifi_only_cfg), GFP_KERNEL);
	else
		rtlpriv->btcoexist.btc_context =
			kzalloc(sizeof(struct btc_coexist), GFP_KERNEL);
}