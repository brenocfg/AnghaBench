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
typedef  int u8 ;
struct mwifiex_sta_node {int dummy; } ;
struct mwifiex_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDLS_CHAN_SWITCHING ; 
 struct mwifiex_sta_node* mwifiex_get_tdls_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 

u8 mwifiex_is_tdls_chan_switching(struct mwifiex_private *priv)
{
	struct mwifiex_sta_node *sta_ptr;

	if (!priv || !ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		return false;

	sta_ptr = mwifiex_get_tdls_sta_entry(priv, TDLS_CHAN_SWITCHING);
	if (sta_ptr)
		return true;

	return false;
}