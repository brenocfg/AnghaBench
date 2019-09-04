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
struct TYPE_2__ {int /*<<< orphan*/ * wifi_only_context; int /*<<< orphan*/ * btc_context; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_btc_free_variable(struct rtl_priv *rtlpriv)
{
	kfree(rtlpriv->btcoexist.btc_context);
	rtlpriv->btcoexist.btc_context = NULL;

	kfree(rtlpriv->btcoexist.wifi_only_context);
	rtlpriv->btcoexist.wifi_only_context = NULL;
}