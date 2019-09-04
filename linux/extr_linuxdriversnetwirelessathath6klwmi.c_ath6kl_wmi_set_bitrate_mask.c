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
struct wmi {struct ath6kl* parent_dev; } ;
struct cfg80211_bitrate_mask {int dummy; } ;
struct ath6kl {int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_64BIT_RATES ; 
 int ath6kl_set_bitrate_mask32 (struct wmi*,int /*<<< orphan*/ ,struct cfg80211_bitrate_mask const*) ; 
 int ath6kl_set_bitrate_mask64 (struct wmi*,int /*<<< orphan*/ ,struct cfg80211_bitrate_mask const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath6kl_wmi_set_bitrate_mask(struct wmi *wmi, u8 if_idx,
				const struct cfg80211_bitrate_mask *mask)
{
	struct ath6kl *ar = wmi->parent_dev;

	if (test_bit(ATH6KL_FW_CAPABILITY_64BIT_RATES,
		     ar->fw_capabilities))
		return ath6kl_set_bitrate_mask64(wmi, if_idx, mask);
	else
		return ath6kl_set_bitrate_mask32(wmi, if_idx, mask);
}