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
typedef  scalar_t__ u64 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ath6kl_vif {scalar_t__ last_roc_id; int /*<<< orphan*/  fw_vif_idx; scalar_t__ last_cancel_roc_id; int /*<<< orphan*/  ndev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ath6kl* ath6kl_priv (int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* ath6kl_vif_from_wdev (struct wireless_dev*) ; 
 int ath6kl_wmi_cancel_remain_on_chnl_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_cancel_remain_on_channel(struct wiphy *wiphy,
					   struct wireless_dev *wdev,
					   u64 cookie)
{
	struct ath6kl_vif *vif = ath6kl_vif_from_wdev(wdev);
	struct ath6kl *ar = ath6kl_priv(vif->ndev);

	if (cookie != vif->last_roc_id)
		return -ENOENT;
	vif->last_cancel_roc_id = cookie;

	return ath6kl_wmi_cancel_remain_on_chnl_cmd(ar->wmi, vif->fw_vif_idx);
}