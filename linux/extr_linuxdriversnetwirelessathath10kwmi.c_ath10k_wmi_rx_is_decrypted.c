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
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {scalar_t__ sw_decrypt_mcast_mgmt; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath10k_wmi_rx_is_decrypted(struct ath10k *ar,
				       struct ieee80211_hdr *hdr)
{
	if (!ieee80211_has_protected(hdr->frame_control))
		return false;

	/* FW delivers WEP Shared Auth frame with Protected Bit set and
	 * encrypted payload. However in case of PMF it delivers decrypted
	 * frames with Protected Bit set.
	 */
	if (ieee80211_is_auth(hdr->frame_control))
		return false;

	/* qca99x0 based FW delivers broadcast or multicast management frames
	 * (ex: group privacy action frames in mesh) as encrypted payload.
	 */
	if (is_multicast_ether_addr(ieee80211_get_DA(hdr)) &&
	    ar->hw_params.sw_decrypt_mcast_mgmt)
		return false;

	return true;
}