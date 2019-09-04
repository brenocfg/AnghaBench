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
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_hdr {int dummy; } ;
struct ath_spec_scan_priv {int dummy; } ;
struct ath_rx_status {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ath_cmn_process_fft(struct ath_spec_scan_priv *spec_priv,
				      struct ieee80211_hdr *hdr,
				      struct ath_rx_status *rs, u64 tsf)
{
	return 0;
}