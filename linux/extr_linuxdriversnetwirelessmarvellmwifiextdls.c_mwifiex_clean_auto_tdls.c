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
struct mwifiex_private {scalar_t__ bss_type; int auto_tdls_timer_active; int /*<<< orphan*/  auto_tdls_timer; TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ auto_tdls; int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 scalar_t__ ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ MWIFIEX_BSS_TYPE_STA ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_flush_auto_tdls_list (struct mwifiex_private*) ; 

void mwifiex_clean_auto_tdls(struct mwifiex_private *priv)
{
	if (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->auto_tdls &&
	    priv->bss_type == MWIFIEX_BSS_TYPE_STA) {
		priv->auto_tdls_timer_active = false;
		del_timer(&priv->auto_tdls_timer);
		mwifiex_flush_auto_tdls_list(priv);
	}
}