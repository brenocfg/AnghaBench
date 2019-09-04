#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_7__ {int action_code; int /*<<< orphan*/  status; int /*<<< orphan*/  timeout; int /*<<< orphan*/  capab; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  capab; } ;
struct TYPE_8__ {TYPE_2__ addba_resp; TYPE_1__ addba_req; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct TYPE_10__ {TYPE_4__ action; } ;
struct ieee80211_mgmt {TYPE_5__ u; } ;
struct ieee80211_hdr {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 int RTL8XXXU_DEBUG_ACTION ; 
#define  WLAN_ACTION_ADDBA_REQ 129 
#define  WLAN_ACTION_ADDBA_RESP 128 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int rtl8xxxu_debug ; 

__attribute__((used)) static void rtl8xxxu_dump_action(struct device *dev,
				 struct ieee80211_hdr *hdr)
{
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)hdr;
	u16 cap, timeout;

	if (!(rtl8xxxu_debug & RTL8XXXU_DEBUG_ACTION))
		return;

	switch (mgmt->u.action.u.addba_resp.action_code) {
	case WLAN_ACTION_ADDBA_RESP:
		cap = le16_to_cpu(mgmt->u.action.u.addba_resp.capab);
		timeout = le16_to_cpu(mgmt->u.action.u.addba_resp.timeout);
		dev_info(dev, "WLAN_ACTION_ADDBA_RESP: "
			 "timeout %i, tid %02x, buf_size %02x, policy %02x, "
			 "status %02x\n",
			 timeout,
			 (cap & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2,
			 (cap & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6,
			 (cap >> 1) & 0x1,
			 le16_to_cpu(mgmt->u.action.u.addba_resp.status));
		break;
	case WLAN_ACTION_ADDBA_REQ:
		cap = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
		timeout = le16_to_cpu(mgmt->u.action.u.addba_req.timeout);
		dev_info(dev, "WLAN_ACTION_ADDBA_REQ: "
			 "timeout %i, tid %02x, buf_size %02x, policy %02x\n",
			 timeout,
			 (cap & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2,
			 (cap & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6,
			 (cap >> 1) & 0x1);
		break;
	default:
		dev_info(dev, "action frame %02x\n",
			 mgmt->u.action.u.addba_resp.action_code);
		break;
	}
}