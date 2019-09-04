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
struct wmi_start_scan_arg {int n_channels; int n_ssids; int n_bssids; scalar_t__ ie_len; } ;
struct wmi_ssid_list {int dummy; } ;
struct wmi_ssid {int dummy; } ;
struct wmi_mac_addr {int dummy; } ;
struct wmi_ie_data {int dummy; } ;
struct wmi_chan_list {int dummy; } ;
struct wmi_bssid_list {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ roundup (scalar_t__,int) ; 

__attribute__((used)) static size_t
ath10k_wmi_start_scan_tlvs_len(const struct wmi_start_scan_arg *arg)
{
	int len = 0;

	if (arg->ie_len) {
		len += sizeof(struct wmi_ie_data);
		len += roundup(arg->ie_len, 4);
	}

	if (arg->n_channels) {
		len += sizeof(struct wmi_chan_list);
		len += sizeof(__le32) * arg->n_channels;
	}

	if (arg->n_ssids) {
		len += sizeof(struct wmi_ssid_list);
		len += sizeof(struct wmi_ssid) * arg->n_ssids;
	}

	if (arg->n_bssids) {
		len += sizeof(struct wmi_bssid_list);
		len += sizeof(struct wmi_mac_addr) * arg->n_bssids;
	}

	return len;
}