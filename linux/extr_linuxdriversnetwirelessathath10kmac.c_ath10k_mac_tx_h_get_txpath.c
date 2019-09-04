#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int target_version_major; } ;
struct TYPE_7__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_4__ htt; TYPE_3__ wmi; TYPE_2__* running_fw; } ;
typedef  enum ath10k_mac_tx_path { ____Placeholder_ath10k_mac_tx_path } ath10k_mac_tx_path ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;
struct TYPE_5__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_6__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX ; 
#define  ATH10K_HW_TXRX_ETHERNET 131 
#define  ATH10K_HW_TXRX_MGMT 130 
#define  ATH10K_HW_TXRX_NATIVE_WIFI 129 
#define  ATH10K_HW_TXRX_RAW 128 
 int ATH10K_MAC_TX_HTT ; 
 int ATH10K_MAC_TX_HTT_MGMT ; 
 int ATH10K_MAC_TX_UNKNOWN ; 
 int ATH10K_MAC_TX_WMI_MGMT ; 
 int /*<<< orphan*/  WMI_SERVICE_MGMT_TX_WMI ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ath10k_mac_tx_path
ath10k_mac_tx_h_get_txpath(struct ath10k *ar,
			   struct sk_buff *skb,
			   enum ath10k_hw_txrx_mode txmode)
{
	switch (txmode) {
	case ATH10K_HW_TXRX_RAW:
	case ATH10K_HW_TXRX_NATIVE_WIFI:
	case ATH10K_HW_TXRX_ETHERNET:
		return ATH10K_MAC_TX_HTT;
	case ATH10K_HW_TXRX_MGMT:
		if (test_bit(ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX,
			     ar->running_fw->fw_file.fw_features) ||
			     test_bit(WMI_SERVICE_MGMT_TX_WMI,
				      ar->wmi.svc_map))
			return ATH10K_MAC_TX_WMI_MGMT;
		else if (ar->htt.target_version_major >= 3)
			return ATH10K_MAC_TX_HTT;
		else
			return ATH10K_MAC_TX_HTT_MGMT;
	}

	return ATH10K_MAC_TX_UNKNOWN;
}