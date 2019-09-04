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
struct wmi_tlv_svc_rdy_parse {int /*<<< orphan*/  service_map_len; struct wlan_host_mem_req const* service_map; int /*<<< orphan*/  num_mem_reqs; int /*<<< orphan*/  high_5ghz_chan; int /*<<< orphan*/  low_5ghz_chan; int /*<<< orphan*/  eeprom_rd; int /*<<< orphan*/  num_rf_chains; int /*<<< orphan*/  phy_capab; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  sw_ver1; int /*<<< orphan*/  sw_ver0; int /*<<< orphan*/  vht_cap; int /*<<< orphan*/  ht_cap; int /*<<< orphan*/  max_tx_power; int /*<<< orphan*/  min_tx_power; struct wlan_host_mem_req* mem_reqs; struct wlan_host_mem_req* svc_bmap; struct hal_reg_capabilities* reg; struct wmi_tlv_svc_rdy_ev* ev; } ;
struct TYPE_2__ {int /*<<< orphan*/  abi_ver1; int /*<<< orphan*/  abi_ver0; int /*<<< orphan*/  abi_ver_ns3; int /*<<< orphan*/  abi_ver_ns2; int /*<<< orphan*/  abi_ver_ns1; int /*<<< orphan*/  abi_ver_ns0; } ;
struct wmi_tlv_svc_rdy_ev {int /*<<< orphan*/  num_mem_reqs; int /*<<< orphan*/  num_rf_chains; int /*<<< orphan*/  phy_capability; int /*<<< orphan*/  fw_build_vers; TYPE_1__ abi; int /*<<< orphan*/  vht_cap_info; int /*<<< orphan*/  ht_cap_info; int /*<<< orphan*/  hw_max_tx_power; int /*<<< orphan*/  hw_min_tx_power; } ;
struct wmi_svc_rdy_ev_arg {int /*<<< orphan*/  service_map_len; struct wlan_host_mem_req const* service_map; int /*<<< orphan*/  num_mem_reqs; int /*<<< orphan*/  high_5ghz_chan; int /*<<< orphan*/  low_5ghz_chan; int /*<<< orphan*/  eeprom_rd; int /*<<< orphan*/  num_rf_chains; int /*<<< orphan*/  phy_capab; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  sw_ver1; int /*<<< orphan*/  sw_ver0; int /*<<< orphan*/  vht_cap; int /*<<< orphan*/  ht_cap; int /*<<< orphan*/  max_tx_power; int /*<<< orphan*/  min_tx_power; struct wlan_host_mem_req* mem_reqs; struct wlan_host_mem_req* svc_bmap; struct hal_reg_capabilities* reg; struct wmi_tlv_svc_rdy_ev* ev; } ;
struct wlan_host_mem_req {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; struct wlan_host_mem_req const* data; } ;
struct hal_reg_capabilities {int /*<<< orphan*/  high_5ghz_chan; int /*<<< orphan*/  low_5ghz_chan; int /*<<< orphan*/  eeprom_rd; } ;
struct ath10k {int dummy; } ;
typedef  struct wlan_host_mem_req __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int ENOTSUPP ; 
 int EPROTO ; 
 scalar_t__ WMI_TLV_ABI_VER0 ; 
 scalar_t__ WMI_TLV_ABI_VER_NS0 ; 
 scalar_t__ WMI_TLV_ABI_VER_NS1 ; 
 scalar_t__ WMI_TLV_ABI_VER_NS2 ; 
 scalar_t__ WMI_TLV_ABI_VER_NS3 ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_tlv_iter (struct ath10k*,struct wlan_host_mem_req const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_tlv_svc_rdy_parse*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_len (struct wlan_host_mem_req const*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_parse_mem_reqs ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_svc_rdy_parse ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_svc_rdy_ev(struct ath10k *ar,
					     struct sk_buff *skb,
					     struct wmi_svc_rdy_ev_arg *arg)
{
	const struct hal_reg_capabilities *reg;
	const struct wmi_tlv_svc_rdy_ev *ev;
	const __le32 *svc_bmap;
	const struct wlan_host_mem_req *mem_reqs;
	struct wmi_tlv_svc_rdy_parse svc_rdy = { };
	int ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_svc_rdy_parse, &svc_rdy);
	if (ret) {
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = svc_rdy.ev;
	reg = svc_rdy.reg;
	svc_bmap = svc_rdy.svc_bmap;
	mem_reqs = svc_rdy.mem_reqs;

	if (!ev || !reg || !svc_bmap || !mem_reqs)
		return -EPROTO;

	/* This is an internal ABI compatibility check for WMI TLV so check it
	 * here instead of the generic WMI code.
	 */
	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv abi 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x\n",
		   __le32_to_cpu(ev->abi.abi_ver0), WMI_TLV_ABI_VER0,
		   __le32_to_cpu(ev->abi.abi_ver_ns0), WMI_TLV_ABI_VER_NS0,
		   __le32_to_cpu(ev->abi.abi_ver_ns1), WMI_TLV_ABI_VER_NS1,
		   __le32_to_cpu(ev->abi.abi_ver_ns2), WMI_TLV_ABI_VER_NS2,
		   __le32_to_cpu(ev->abi.abi_ver_ns3), WMI_TLV_ABI_VER_NS3);

	if (__le32_to_cpu(ev->abi.abi_ver0) != WMI_TLV_ABI_VER0 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns0) != WMI_TLV_ABI_VER_NS0 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns1) != WMI_TLV_ABI_VER_NS1 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns2) != WMI_TLV_ABI_VER_NS2 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns3) != WMI_TLV_ABI_VER_NS3) {
		return -ENOTSUPP;
	}

	arg->min_tx_power = ev->hw_min_tx_power;
	arg->max_tx_power = ev->hw_max_tx_power;
	arg->ht_cap = ev->ht_cap_info;
	arg->vht_cap = ev->vht_cap_info;
	arg->sw_ver0 = ev->abi.abi_ver0;
	arg->sw_ver1 = ev->abi.abi_ver1;
	arg->fw_build = ev->fw_build_vers;
	arg->phy_capab = ev->phy_capability;
	arg->num_rf_chains = ev->num_rf_chains;
	arg->eeprom_rd = reg->eeprom_rd;
	arg->low_5ghz_chan = reg->low_5ghz_chan;
	arg->high_5ghz_chan = reg->high_5ghz_chan;
	arg->num_mem_reqs = ev->num_mem_reqs;
	arg->service_map = svc_bmap;
	arg->service_map_len = ath10k_wmi_tlv_len(svc_bmap);

	ret = ath10k_wmi_tlv_iter(ar, mem_reqs, ath10k_wmi_tlv_len(mem_reqs),
				  ath10k_wmi_tlv_parse_mem_reqs, arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse mem_reqs tlv: %d\n", ret);
		return ret;
	}

	return 0;
}