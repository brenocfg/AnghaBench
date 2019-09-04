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
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_le_meta {int subevent; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
#define  HCI_EV_LE_ADVERTISING_REPORT 137 
#define  HCI_EV_LE_CONN_COMPLETE 136 
#define  HCI_EV_LE_CONN_UPDATE_COMPLETE 135 
#define  HCI_EV_LE_DIRECT_ADV_REPORT 134 
#define  HCI_EV_LE_ENHANCED_CONN_COMPLETE 133 
#define  HCI_EV_LE_EXT_ADV_REPORT 132 
#define  HCI_EV_LE_EXT_ADV_SET_TERM 131 
#define  HCI_EV_LE_LTK_REQ 130 
#define  HCI_EV_LE_REMOTE_CONN_PARAM_REQ 129 
#define  HCI_EV_LE_REMOTE_FEAT_COMPLETE 128 
 int /*<<< orphan*/  hci_le_adv_report_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_conn_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_conn_update_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_direct_adv_report_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_enh_conn_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_ext_adv_report_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_ext_adv_term_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_ltk_request_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_remote_conn_param_req_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_le_remote_feat_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void hci_le_meta_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_le_meta *le_ev = (void *) skb->data;

	skb_pull(skb, sizeof(*le_ev));

	switch (le_ev->subevent) {
	case HCI_EV_LE_CONN_COMPLETE:
		hci_le_conn_complete_evt(hdev, skb);
		break;

	case HCI_EV_LE_CONN_UPDATE_COMPLETE:
		hci_le_conn_update_complete_evt(hdev, skb);
		break;

	case HCI_EV_LE_ADVERTISING_REPORT:
		hci_le_adv_report_evt(hdev, skb);
		break;

	case HCI_EV_LE_REMOTE_FEAT_COMPLETE:
		hci_le_remote_feat_complete_evt(hdev, skb);
		break;

	case HCI_EV_LE_LTK_REQ:
		hci_le_ltk_request_evt(hdev, skb);
		break;

	case HCI_EV_LE_REMOTE_CONN_PARAM_REQ:
		hci_le_remote_conn_param_req_evt(hdev, skb);
		break;

	case HCI_EV_LE_DIRECT_ADV_REPORT:
		hci_le_direct_adv_report_evt(hdev, skb);
		break;

	case HCI_EV_LE_EXT_ADV_REPORT:
		hci_le_ext_adv_report_evt(hdev, skb);
		break;

	case HCI_EV_LE_ENHANCED_CONN_COMPLETE:
		hci_le_enh_conn_complete_evt(hdev, skb);
		break;

	case HCI_EV_LE_EXT_ADV_SET_TERM:
		hci_le_ext_adv_term_evt(hdev, skb);
		break;

	default:
		break;
	}
}