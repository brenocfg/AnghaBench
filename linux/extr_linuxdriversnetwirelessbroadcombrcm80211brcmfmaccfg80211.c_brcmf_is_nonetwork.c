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
typedef  scalar_t__ u32 ;
struct brcmf_event_msg {scalar_t__ event_code; scalar_t__ status; int flags; } ;
struct brcmf_cfg80211_info {int dummy; } ;

/* Variables and functions */
 int BRCMF_EVENT_MSG_LINK ; 
 scalar_t__ BRCMF_E_LINK ; 
 scalar_t__ BRCMF_E_PSK_SUP ; 
 scalar_t__ BRCMF_E_SET_SSID ; 
 scalar_t__ BRCMF_E_STATUS_FWSUP_COMPLETED ; 
 scalar_t__ BRCMF_E_STATUS_NO_NETWORKS ; 
 scalar_t__ BRCMF_E_STATUS_SUCCESS ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool brcmf_is_nonetwork(struct brcmf_cfg80211_info *cfg,
			       const struct brcmf_event_msg *e)
{
	u32 event = e->event_code;
	u32 status = e->status;

	if (event == BRCMF_E_LINK && status == BRCMF_E_STATUS_NO_NETWORKS) {
		brcmf_dbg(CONN, "Processing Link %s & no network found\n",
			  e->flags & BRCMF_EVENT_MSG_LINK ? "up" : "down");
		return true;
	}

	if (event == BRCMF_E_SET_SSID && status != BRCMF_E_STATUS_SUCCESS) {
		brcmf_dbg(CONN, "Processing connecting & no network found\n");
		return true;
	}

	if (event == BRCMF_E_PSK_SUP &&
	    status != BRCMF_E_STATUS_FWSUP_COMPLETED) {
		brcmf_dbg(CONN, "Processing failed supplicant state: %u\n",
			  status);
		return true;
	}

	return false;
}