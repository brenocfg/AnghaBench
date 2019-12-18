#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {TYPE_5__* netdev; TYPE_4__* current_bss; int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {int /*<<< orphan*/  reason_code; } ;
struct TYPE_8__ {TYPE_1__ disassoc; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; TYPE_2__ u; int /*<<< orphan*/ * bssid; } ;
struct cfg80211_registered_device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  const* dev_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_10__ {TYPE_3__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __cfg80211_disconnected (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_sme_disassoc (struct wireless_dev*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_send_disassoc (struct cfg80211_registered_device*,TYPE_5__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg80211_process_disassoc(struct wireless_dev *wdev,
				      const u8 *buf, size_t len)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)buf;
	const u8 *bssid = mgmt->bssid;
	u16 reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);
	bool from_ap = !ether_addr_equal(mgmt->sa, wdev->netdev->dev_addr);

	nl80211_send_disassoc(rdev, wdev->netdev, buf, len, GFP_KERNEL);

	if (WARN_ON(!wdev->current_bss ||
		    !ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		return;

	__cfg80211_disconnected(wdev->netdev, NULL, 0, reason_code, from_ap);
	cfg80211_sme_disassoc(wdev);
}