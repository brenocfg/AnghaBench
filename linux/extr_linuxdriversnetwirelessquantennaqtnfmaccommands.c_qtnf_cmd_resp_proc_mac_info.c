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
struct qtnf_mac_info {int /*<<< orphan*/  vht_cap_mod_mask; int /*<<< orphan*/  ht_cap_mod_mask; int /*<<< orphan*/  max_acl_mac_addrs; int /*<<< orphan*/  radar_detect_widths; int /*<<< orphan*/  max_ap_assoc_sta; int /*<<< orphan*/  num_rx_chain; int /*<<< orphan*/  num_tx_chain; int /*<<< orphan*/  dev_mac; int /*<<< orphan*/  bands_cap; } ;
struct qtnf_wmac {int /*<<< orphan*/  macaddr; struct qtnf_mac_info macinfo; } ;
struct qtnf_vif {int /*<<< orphan*/  mac_addr; } ;
struct qlink_resp_get_mac_info {int /*<<< orphan*/  vht_cap_mod_mask; int /*<<< orphan*/  ht_cap_mod_mask; int /*<<< orphan*/  max_acl_mac_addrs; int /*<<< orphan*/  radar_detect_widths; int /*<<< orphan*/  max_ap_assoc_sta; int /*<<< orphan*/  num_rx_chain; int /*<<< orphan*/  num_tx_chain; int /*<<< orphan*/  dev_mac; int /*<<< orphan*/  bands_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qlink_chan_width_mask_to_nl (int /*<<< orphan*/ ) ; 
 struct qtnf_vif* qtnf_mac_get_base_vif (struct qtnf_wmac*) ; 

__attribute__((used)) static void
qtnf_cmd_resp_proc_mac_info(struct qtnf_wmac *mac,
			    const struct qlink_resp_get_mac_info *resp_info)
{
	struct qtnf_mac_info *mac_info;
	struct qtnf_vif *vif;

	mac_info = &mac->macinfo;

	mac_info->bands_cap = resp_info->bands_cap;
	memcpy(&mac_info->dev_mac, &resp_info->dev_mac,
	       sizeof(mac_info->dev_mac));

	ether_addr_copy(mac->macaddr, mac_info->dev_mac);

	vif = qtnf_mac_get_base_vif(mac);
	if (vif)
		ether_addr_copy(vif->mac_addr, mac->macaddr);
	else
		pr_err("could not get valid base vif\n");

	mac_info->num_tx_chain = resp_info->num_tx_chain;
	mac_info->num_rx_chain = resp_info->num_rx_chain;

	mac_info->max_ap_assoc_sta = le16_to_cpu(resp_info->max_ap_assoc_sta);
	mac_info->radar_detect_widths =
			qlink_chan_width_mask_to_nl(le16_to_cpu(
					resp_info->radar_detect_widths));
	mac_info->max_acl_mac_addrs = le32_to_cpu(resp_info->max_acl_mac_addrs);

	memcpy(&mac_info->ht_cap_mod_mask, &resp_info->ht_cap_mod_mask,
	       sizeof(mac_info->ht_cap_mod_mask));
	memcpy(&mac_info->vht_cap_mod_mask, &resp_info->vht_cap_mod_mask,
	       sizeof(mac_info->vht_cap_mod_mask));
}