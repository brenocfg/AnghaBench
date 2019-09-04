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
struct sk_buff {scalar_t__ data; } ;
struct mwifiex_radar_det_event {int /*<<< orphan*/  det_type; int /*<<< orphan*/  reg_domain; } ;
struct mwifiex_private {TYPE_1__* adapter; int /*<<< orphan*/  dfs_chandef; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  cfg80211_radar_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_stop_radar_detection (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

int mwifiex_11h_handle_radar_detected(struct mwifiex_private *priv,
				      struct sk_buff *skb)
{
	struct mwifiex_radar_det_event *rdr_event;

	rdr_event = (void *)(skb->data + sizeof(u32));

	mwifiex_dbg(priv->adapter, MSG,
		    "radar detected; indicating kernel\n");
	if (mwifiex_stop_radar_detection(priv, &priv->dfs_chandef))
		mwifiex_dbg(priv->adapter, ERROR,
			    "Failed to stop CAC in FW\n");
	cfg80211_radar_event(priv->adapter->wiphy, &priv->dfs_chandef,
			     GFP_KERNEL);
	mwifiex_dbg(priv->adapter, MSG, "regdomain: %d\n",
		    rdr_event->reg_domain);
	mwifiex_dbg(priv->adapter, MSG, "radar detection type: %d\n",
		    rdr_event->det_type);

	return 0;
}