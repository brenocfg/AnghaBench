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
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int /*<<< orphan*/  usr_dot_11ac_dev_cap_bg; int /*<<< orphan*/  usr_dot_11ac_dev_cap_a; } ;
struct ieee80211_vht_cap {void* vht_cap_info; } ;

/* Variables and functions */
 int BAND_A ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwifiex_fill_vht_cap_info(struct mwifiex_private *priv,
			  struct ieee80211_vht_cap *vht_cap, u8 bands)
{
	struct mwifiex_adapter *adapter = priv->adapter;

	if (bands & BAND_A)
		vht_cap->vht_cap_info =
				cpu_to_le32(adapter->usr_dot_11ac_dev_cap_a);
	else
		vht_cap->vht_cap_info =
				cpu_to_le32(adapter->usr_dot_11ac_dev_cap_bg);
}