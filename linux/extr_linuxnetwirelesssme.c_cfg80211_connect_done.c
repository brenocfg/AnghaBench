#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  event_work; } ;
struct cfg80211_internal_bss {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int kek_len; int pmk_len; int /*<<< orphan*/  erp_next_seq_num; scalar_t__ update_erp_next_seq_num; int /*<<< orphan*/ * pmkid; int /*<<< orphan*/ * pmk; int /*<<< orphan*/ * kek; } ;
struct TYPE_6__ {int req_ie_len; int resp_ie_len; int /*<<< orphan*/  timeout_reason; int /*<<< orphan*/  status; int /*<<< orphan*/  bss; TYPE_1__ fils; int /*<<< orphan*/ * resp_ie; int /*<<< orphan*/ * req_ie; int /*<<< orphan*/ * bssid; } ;
struct cfg80211_event {int /*<<< orphan*/  list; TYPE_3__ cr; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int kek_len; int pmk_len; int /*<<< orphan*/  erp_next_seq_num; scalar_t__ update_erp_next_seq_num; scalar_t__ pmkid; scalar_t__ pmk; scalar_t__ kek; } ;
struct cfg80211_connect_resp_params {int req_ie_len; int resp_ie_len; int /*<<< orphan*/  timeout_reason; int /*<<< orphan*/  status; int /*<<< orphan*/  bss; TYPE_2__ fils; scalar_t__ resp_ie; scalar_t__ req_ie; scalar_t__ bssid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_CONNECT_RESULT ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int WLAN_PMKID_LEN ; 
 struct cfg80211_internal_bss* bss_from_pub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (struct cfg80211_internal_bss*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 struct cfg80211_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void cfg80211_connect_done(struct net_device *dev,
			   struct cfg80211_connect_resp_params *params,
			   gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct cfg80211_event *ev;
	unsigned long flags;
	u8 *next;

	if (params->bss) {
		/* Make sure the bss entry provided by the driver is valid. */
		struct cfg80211_internal_bss *ibss = bss_from_pub(params->bss);

		if (WARN_ON(list_empty(&ibss->list))) {
			cfg80211_put_bss(wdev->wiphy, params->bss);
			return;
		}
	}

	ev = kzalloc(sizeof(*ev) + (params->bssid ? ETH_ALEN : 0) +
		     params->req_ie_len + params->resp_ie_len +
		     params->fils.kek_len + params->fils.pmk_len +
		     (params->fils.pmkid ? WLAN_PMKID_LEN : 0), gfp);
	if (!ev) {
		cfg80211_put_bss(wdev->wiphy, params->bss);
		return;
	}

	ev->type = EVENT_CONNECT_RESULT;
	next = ((u8 *)ev) + sizeof(*ev);
	if (params->bssid) {
		ev->cr.bssid = next;
		memcpy((void *)ev->cr.bssid, params->bssid, ETH_ALEN);
		next += ETH_ALEN;
	}
	if (params->req_ie_len) {
		ev->cr.req_ie = next;
		ev->cr.req_ie_len = params->req_ie_len;
		memcpy((void *)ev->cr.req_ie, params->req_ie,
		       params->req_ie_len);
		next += params->req_ie_len;
	}
	if (params->resp_ie_len) {
		ev->cr.resp_ie = next;
		ev->cr.resp_ie_len = params->resp_ie_len;
		memcpy((void *)ev->cr.resp_ie, params->resp_ie,
		       params->resp_ie_len);
		next += params->resp_ie_len;
	}
	if (params->fils.kek_len) {
		ev->cr.fils.kek = next;
		ev->cr.fils.kek_len = params->fils.kek_len;
		memcpy((void *)ev->cr.fils.kek, params->fils.kek,
		       params->fils.kek_len);
		next += params->fils.kek_len;
	}
	if (params->fils.pmk_len) {
		ev->cr.fils.pmk = next;
		ev->cr.fils.pmk_len = params->fils.pmk_len;
		memcpy((void *)ev->cr.fils.pmk, params->fils.pmk,
		       params->fils.pmk_len);
		next += params->fils.pmk_len;
	}
	if (params->fils.pmkid) {
		ev->cr.fils.pmkid = next;
		memcpy((void *)ev->cr.fils.pmkid, params->fils.pmkid,
		       WLAN_PMKID_LEN);
		next += WLAN_PMKID_LEN;
	}
	ev->cr.fils.update_erp_next_seq_num = params->fils.update_erp_next_seq_num;
	if (params->fils.update_erp_next_seq_num)
		ev->cr.fils.erp_next_seq_num = params->fils.erp_next_seq_num;
	if (params->bss)
		cfg80211_hold_bss(bss_from_pub(params->bss));
	ev->cr.bss = params->bss;
	ev->cr.status = params->status;
	ev->cr.timeout_reason = params->timeout_reason;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
}