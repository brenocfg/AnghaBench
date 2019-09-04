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
struct mwifiex_sta_node {int is_11n_enabled; } ;
struct mwifiex_private {scalar_t__ bss_role; scalar_t__ bss_mode; TYPE_1__* adapter; int /*<<< orphan*/  ap_11n_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  adhoc_11n_enabled; } ;

/* Variables and functions */
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 

__attribute__((used)) static inline int mwifiex_is_sta_11n_enabled(struct mwifiex_private *priv,
					     struct mwifiex_sta_node *node)
{
	if (!node || ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP) &&
		      !priv->ap_11n_enabled) ||
	    ((priv->bss_mode == NL80211_IFTYPE_ADHOC) &&
	     !priv->adapter->adhoc_11n_enabled))
		return 0;

	return node->is_11n_enabled;
}