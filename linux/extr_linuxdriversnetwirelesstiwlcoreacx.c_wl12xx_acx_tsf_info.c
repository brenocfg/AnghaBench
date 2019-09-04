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
typedef  int u64 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl12xx_acx_fw_tsf_information {int /*<<< orphan*/  current_tsf_high; int /*<<< orphan*/  current_tsf_low; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct acx_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_TSF_INFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_acx_fw_tsf_information*) ; 
 struct wl12xx_acx_fw_tsf_information* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int wl1271_cmd_interrogate (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_acx_fw_tsf_information*,int,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl12xx_acx_tsf_info(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			u64 *mactime)
{
	struct wl12xx_acx_fw_tsf_information *tsf_info;
	int ret;

	tsf_info = kzalloc(sizeof(*tsf_info), GFP_KERNEL);
	if (!tsf_info) {
		ret = -ENOMEM;
		goto out;
	}

	tsf_info->role_id = wlvif->role_id;

	ret = wl1271_cmd_interrogate(wl, ACX_TSF_INFO, tsf_info,
				sizeof(struct acx_header), sizeof(*tsf_info));
	if (ret < 0) {
		wl1271_warning("acx tsf info interrogate failed");
		goto out;
	}

	*mactime = le32_to_cpu(tsf_info->current_tsf_low) |
		((u64) le32_to_cpu(tsf_info->current_tsf_high) << 32);

out:
	kfree(tsf_info);
	return ret;
}