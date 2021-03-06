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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_CMD_ASSOCIATE ; 
 int /*<<< orphan*/  nl80211_send_mlme_event (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 

void nl80211_send_rx_assoc(struct cfg80211_registered_device *rdev,
			   struct net_device *netdev, const u8 *buf,
			   size_t len, gfp_t gfp, int uapsd_queues,
			   const u8 *req_ies, size_t req_ies_len)
{
	nl80211_send_mlme_event(rdev, netdev, buf, len,
				NL80211_CMD_ASSOCIATE, gfp, uapsd_queues,
				req_ies, req_ies_len);
}