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
typedef  void* u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct hci_cp_le_set_scan_param {void* filter_dup; void* enable; void* filter_policy; void* own_address_type; void* window; void* interval; void* type; int /*<<< orphan*/  scanning_phys; void* own_addr_type; scalar_t__ data; } ;
struct hci_cp_le_set_scan_enable {void* filter_dup; void* enable; void* filter_policy; void* own_address_type; void* window; void* interval; void* type; int /*<<< orphan*/  scanning_phys; void* own_addr_type; scalar_t__ data; } ;
struct hci_cp_le_set_ext_scan_params {void* filter_dup; void* enable; void* filter_policy; void* own_address_type; void* window; void* interval; void* type; int /*<<< orphan*/  scanning_phys; void* own_addr_type; scalar_t__ data; } ;
struct hci_cp_le_set_ext_scan_enable {void* filter_dup; void* enable; void* filter_policy; void* own_address_type; void* window; void* interval; void* type; int /*<<< orphan*/  scanning_phys; void* own_addr_type; scalar_t__ data; } ;
struct hci_cp_le_scan_phy_params {void* filter_dup; void* enable; void* filter_policy; void* own_address_type; void* window; void* interval; void* type; int /*<<< orphan*/  scanning_phys; void* own_addr_type; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  param_cp ;
typedef  int /*<<< orphan*/  ext_enable_cp ;
typedef  int /*<<< orphan*/  enable_cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_SCAN_ENABLE ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_SCAN_PARAMS ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_SCAN_ENABLE ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_SCAN_PARAM ; 
 void* LE_SCAN_ENABLE ; 
 void* LE_SCAN_FILTER_DUP_ENABLE ; 
 int /*<<< orphan*/  LE_SCAN_PHY_1M ; 
 int /*<<< orphan*/  LE_SCAN_PHY_CODED ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_le_set_scan_param*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_scan_param*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scan_1m (struct hci_dev*) ; 
 scalar_t__ scan_2m (struct hci_dev*) ; 
 scalar_t__ scan_coded (struct hci_dev*) ; 
 scalar_t__ use_ext_scan (struct hci_dev*) ; 

__attribute__((used)) static void hci_req_start_scan(struct hci_request *req, u8 type, u16 interval,
			       u16 window, u8 own_addr_type, u8 filter_policy)
{
	struct hci_dev *hdev = req->hdev;

	/* Use ext scanning if set ext scan param and ext scan enable is
	 * supported
	 */
	if (use_ext_scan(hdev)) {
		struct hci_cp_le_set_ext_scan_params *ext_param_cp;
		struct hci_cp_le_set_ext_scan_enable ext_enable_cp;
		struct hci_cp_le_scan_phy_params *phy_params;
		u8 data[sizeof(*ext_param_cp) + sizeof(*phy_params) * 2];
		u32 plen;

		ext_param_cp = (void *)data;
		phy_params = (void *)ext_param_cp->data;

		memset(ext_param_cp, 0, sizeof(*ext_param_cp));
		ext_param_cp->own_addr_type = own_addr_type;
		ext_param_cp->filter_policy = filter_policy;

		plen = sizeof(*ext_param_cp);

		if (scan_1m(hdev) || scan_2m(hdev)) {
			ext_param_cp->scanning_phys |= LE_SCAN_PHY_1M;

			memset(phy_params, 0, sizeof(*phy_params));
			phy_params->type = type;
			phy_params->interval = cpu_to_le16(interval);
			phy_params->window = cpu_to_le16(window);

			plen += sizeof(*phy_params);
			phy_params++;
		}

		if (scan_coded(hdev)) {
			ext_param_cp->scanning_phys |= LE_SCAN_PHY_CODED;

			memset(phy_params, 0, sizeof(*phy_params));
			phy_params->type = type;
			phy_params->interval = cpu_to_le16(interval);
			phy_params->window = cpu_to_le16(window);

			plen += sizeof(*phy_params);
			phy_params++;
		}

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_PARAMS,
			    plen, ext_param_cp);

		memset(&ext_enable_cp, 0, sizeof(ext_enable_cp));
		ext_enable_cp.enable = LE_SCAN_ENABLE;
		ext_enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_ENABLE,
			    sizeof(ext_enable_cp), &ext_enable_cp);
	} else {
		struct hci_cp_le_set_scan_param param_cp;
		struct hci_cp_le_set_scan_enable enable_cp;

		memset(&param_cp, 0, sizeof(param_cp));
		param_cp.type = type;
		param_cp.interval = cpu_to_le16(interval);
		param_cp.window = cpu_to_le16(window);
		param_cp.own_address_type = own_addr_type;
		param_cp.filter_policy = filter_policy;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_PARAM, sizeof(param_cp),
			    &param_cp);

		memset(&enable_cp, 0, sizeof(enable_cp));
		enable_cp.enable = LE_SCAN_ENABLE;
		enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_ENABLE, sizeof(enable_cp),
			    &enable_cp);
	}
}