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
struct sta_info {int tx_supp_rates; int* supported_rates; int tx_max_rate; int tx_rate; int tx_rate_idx; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int WLAN_RATE_11M ; 
 int WLAN_RATE_1M ; 
 int WLAN_RATE_2M ; 
 int WLAN_RATE_5M5 ; 
 scalar_t__ ap_tx_rate_ok (int,struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prism2_check_tx_rates(struct sta_info *sta)
{
	int i;

	sta->tx_supp_rates = 0;
	for (i = 0; i < sizeof(sta->supported_rates); i++) {
		if ((sta->supported_rates[i] & 0x7f) == 2)
			sta->tx_supp_rates |= WLAN_RATE_1M;
		if ((sta->supported_rates[i] & 0x7f) == 4)
			sta->tx_supp_rates |= WLAN_RATE_2M;
		if ((sta->supported_rates[i] & 0x7f) == 11)
			sta->tx_supp_rates |= WLAN_RATE_5M5;
		if ((sta->supported_rates[i] & 0x7f) == 22)
			sta->tx_supp_rates |= WLAN_RATE_11M;
	}
	sta->tx_max_rate = sta->tx_rate = sta->tx_rate_idx = 0;
	if (sta->tx_supp_rates & WLAN_RATE_1M) {
		sta->tx_max_rate = 0;
		if (ap_tx_rate_ok(0, sta, sta->local)) {
			sta->tx_rate = 10;
			sta->tx_rate_idx = 0;
		}
	}
	if (sta->tx_supp_rates & WLAN_RATE_2M) {
		sta->tx_max_rate = 1;
		if (ap_tx_rate_ok(1, sta, sta->local)) {
			sta->tx_rate = 20;
			sta->tx_rate_idx = 1;
		}
	}
	if (sta->tx_supp_rates & WLAN_RATE_5M5) {
		sta->tx_max_rate = 2;
		if (ap_tx_rate_ok(2, sta, sta->local)) {
			sta->tx_rate = 55;
			sta->tx_rate_idx = 2;
		}
	}
	if (sta->tx_supp_rates & WLAN_RATE_11M) {
		sta->tx_max_rate = 3;
		if (ap_tx_rate_ok(3, sta, sta->local)) {
			sta->tx_rate = 110;
			sta->tx_rate_idx = 3;
		}
	}
}