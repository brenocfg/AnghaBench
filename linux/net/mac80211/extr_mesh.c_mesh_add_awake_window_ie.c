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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dot11MeshAwakeWindowDuration; } ;
struct ieee80211_if_mesh {scalar_t__ ps_peers_light_sleep; scalar_t__ ps_peers_deep_sleep; scalar_t__ nonpeer_pm; TYPE_1__ mshcfg; } ;
struct TYPE_4__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NL80211_MESH_POWER_ACTIVE ; 
 int /*<<< orphan*/  WLAN_EID_MESH_AWAKE_WINDOW ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int mesh_add_awake_window_ie(struct ieee80211_sub_if_data *sdata,
				    struct sk_buff *skb)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 *pos;

	/* see IEEE802.11-2012 13.14.6 */
	if (ifmsh->ps_peers_light_sleep == 0 &&
	    ifmsh->ps_peers_deep_sleep == 0 &&
	    ifmsh->nonpeer_pm == NL80211_MESH_POWER_ACTIVE)
		return 0;

	if (skb_tailroom(skb) < 4)
		return -ENOMEM;

	pos = skb_put(skb, 2 + 2);
	*pos++ = WLAN_EID_MESH_AWAKE_WINDOW;
	*pos++ = 2;
	put_unaligned_le16(ifmsh->mshcfg.dot11MeshAwakeWindowDuration, pos);

	return 0;
}