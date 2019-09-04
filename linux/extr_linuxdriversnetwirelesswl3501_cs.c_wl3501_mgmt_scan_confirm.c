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
typedef  size_t u16 ;
struct TYPE_6__ {int len; } ;
struct TYPE_7__ {char* essid; TYPE_1__ el; } ;
struct wl3501_scan_confirm {scalar_t__ status; int cap_info; int /*<<< orphan*/  rssi; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  bssid; TYPE_2__ ssid; } ;
struct TYPE_8__ {int len; } ;
struct TYPE_9__ {TYPE_3__ el; int /*<<< orphan*/  essid; } ;
struct wl3501_card {scalar_t__ net_type; size_t bss_cnt; size_t join_sta_bss; scalar_t__ adhoc_times; int /*<<< orphan*/  rssi; TYPE_5__* bss_set; TYPE_4__ essid; } ;
typedef  int /*<<< orphan*/  sig ;
struct TYPE_10__ {int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_AUTO ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ WL3501_MAX_ADHOC_TRIES ; 
 int WL3501_MGMT_CAPABILITY_ESS ; 
 int WL3501_MGMT_CAPABILITY_IBSS ; 
 scalar_t__ WL3501_STATUS_SUCCESS ; 
 scalar_t__ WL3501_STATUS_TIMEOUT ; 
 scalar_t__ ether_addr_equal_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,size_t,struct wl3501_scan_confirm*,int) ; 
 int /*<<< orphan*/  wl3501_mgmt_join (struct wl3501_card*,size_t) ; 
 int /*<<< orphan*/  wl3501_mgmt_scan (struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_mgmt_start (struct wl3501_card*) ; 

__attribute__((used)) static void wl3501_mgmt_scan_confirm(struct wl3501_card *this, u16 addr)
{
	u16 i = 0;
	int matchflag = 0;
	struct wl3501_scan_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, sizeof(sig));
	if (sig.status == WL3501_STATUS_SUCCESS) {
		pr_debug("success");
		if ((this->net_type == IW_MODE_INFRA &&
		     (sig.cap_info & WL3501_MGMT_CAPABILITY_ESS)) ||
		    (this->net_type == IW_MODE_ADHOC &&
		     (sig.cap_info & WL3501_MGMT_CAPABILITY_IBSS)) ||
		    this->net_type == IW_MODE_AUTO) {
			if (!this->essid.el.len)
				matchflag = 1;
			else if (this->essid.el.len == 3 &&
				 !memcmp(this->essid.essid, "ANY", 3))
				matchflag = 1;
			else if (this->essid.el.len != sig.ssid.el.len)
				matchflag = 0;
			else if (memcmp(this->essid.essid, sig.ssid.essid,
					this->essid.el.len))
				matchflag = 0;
			else
				matchflag = 1;
			if (matchflag) {
				for (i = 0; i < this->bss_cnt; i++) {
					if (ether_addr_equal_unaligned(this->bss_set[i].bssid, sig.bssid)) {
						matchflag = 0;
						break;
					}
				}
			}
			if (matchflag && (i < 20)) {
				memcpy(&this->bss_set[i].beacon_period,
				       &sig.beacon_period, 73);
				this->bss_cnt++;
				this->rssi = sig.rssi;
			}
		}
	} else if (sig.status == WL3501_STATUS_TIMEOUT) {
		pr_debug("timeout");
		this->join_sta_bss = 0;
		for (i = this->join_sta_bss; i < this->bss_cnt; i++)
			if (!wl3501_mgmt_join(this, i))
				break;
		this->join_sta_bss = i;
		if (this->join_sta_bss == this->bss_cnt) {
			if (this->net_type == IW_MODE_INFRA)
				wl3501_mgmt_scan(this, 100);
			else {
				this->adhoc_times++;
				if (this->adhoc_times > WL3501_MAX_ADHOC_TRIES)
					wl3501_mgmt_start(this);
				else
					wl3501_mgmt_scan(this, 100);
			}
		}
	}
}