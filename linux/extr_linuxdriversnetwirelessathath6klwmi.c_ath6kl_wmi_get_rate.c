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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct wmi {struct ath6kl* parent_dev; } ;
struct ath6kl {int /*<<< orphan*/  fw_capabilities; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_RATETABLE_MCS15 ; 
 int RATE_AUTO ; 
 int RATE_INDEX_MSB ; 
 int RATE_INDEX_WITHOUT_SGI_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** wmi_rate_tbl ; 
 int /*<<< orphan*/ ** wmi_rate_tbl_mcs15 ; 

s32 ath6kl_wmi_get_rate(struct wmi *wmi, s8 rate_index)
{
	struct ath6kl *ar = wmi->parent_dev;
	u8 sgi = 0;
	s32 ret;

	if (rate_index == RATE_AUTO)
		return 0;

	/* SGI is stored as the MSB of the rate_index */
	if (rate_index & RATE_INDEX_MSB) {
		rate_index &= RATE_INDEX_WITHOUT_SGI_MASK;
		sgi = 1;
	}

	if (test_bit(ATH6KL_FW_CAPABILITY_RATETABLE_MCS15,
		     ar->fw_capabilities)) {
		if (WARN_ON(rate_index >= ARRAY_SIZE(wmi_rate_tbl_mcs15)))
			return 0;

		ret = wmi_rate_tbl_mcs15[(u32) rate_index][sgi];
	} else {
		if (WARN_ON(rate_index >= ARRAY_SIZE(wmi_rate_tbl)))
			return 0;

		ret = wmi_rate_tbl[(u32) rate_index][sgi];
	}

	return ret;
}