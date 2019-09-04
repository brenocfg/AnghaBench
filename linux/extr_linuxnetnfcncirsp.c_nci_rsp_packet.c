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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  cmd_timer; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  NCI_CTRL_HDR_SIZE ; 
 scalar_t__ NCI_GID_PROPRIETARY ; 
#define  NCI_OP_CORE_CONN_CLOSE_RSP 138 
#define  NCI_OP_CORE_CONN_CREATE_RSP 137 
#define  NCI_OP_CORE_INIT_RSP 136 
#define  NCI_OP_CORE_RESET_RSP 135 
#define  NCI_OP_CORE_SET_CONFIG_RSP 134 
#define  NCI_OP_NFCEE_DISCOVER_RSP 133 
#define  NCI_OP_NFCEE_MODE_SET_RSP 132 
#define  NCI_OP_RF_DEACTIVATE_RSP 131 
#define  NCI_OP_RF_DISCOVER_MAP_RSP 130 
#define  NCI_OP_RF_DISCOVER_RSP 129 
#define  NCI_OP_RF_DISCOVER_SELECT_RSP 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_conn_close_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_conn_create_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_init_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_reset_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_rsp_packet (struct nci_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_set_config_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_nfcee_discover_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_nfcee_mode_set_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int nci_opcode (int /*<<< orphan*/ ) ; 
 scalar_t__ nci_opcode_gid (int) ; 
 int /*<<< orphan*/  nci_opcode_oid (int) ; 
 int /*<<< orphan*/  nci_pbf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_plen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_prop_rsp_packet (struct nci_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_deactivate_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_disc_map_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_disc_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_disc_select_rsp_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

void nci_rsp_packet(struct nci_dev *ndev, struct sk_buff *skb)
{
	__u16 rsp_opcode = nci_opcode(skb->data);

	/* we got a rsp, stop the cmd timer */
	del_timer(&ndev->cmd_timer);

	pr_debug("NCI RX: MT=rsp, PBF=%d, GID=0x%x, OID=0x%x, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(rsp_opcode),
		 nci_opcode_oid(rsp_opcode),
		 nci_plen(skb->data));

	/* strip the nci control header */
	skb_pull(skb, NCI_CTRL_HDR_SIZE);

	if (nci_opcode_gid(rsp_opcode) == NCI_GID_PROPRIETARY) {
		if (nci_prop_rsp_packet(ndev, rsp_opcode, skb) == -ENOTSUPP) {
			pr_err("unsupported rsp opcode 0x%x\n",
			       rsp_opcode);
		}

		goto end;
	}

	switch (rsp_opcode) {
	case NCI_OP_CORE_RESET_RSP:
		nci_core_reset_rsp_packet(ndev, skb);
		break;

	case NCI_OP_CORE_INIT_RSP:
		nci_core_init_rsp_packet(ndev, skb);
		break;

	case NCI_OP_CORE_SET_CONFIG_RSP:
		nci_core_set_config_rsp_packet(ndev, skb);
		break;

	case NCI_OP_CORE_CONN_CREATE_RSP:
		nci_core_conn_create_rsp_packet(ndev, skb);
		break;

	case NCI_OP_CORE_CONN_CLOSE_RSP:
		nci_core_conn_close_rsp_packet(ndev, skb);
		break;

	case NCI_OP_RF_DISCOVER_MAP_RSP:
		nci_rf_disc_map_rsp_packet(ndev, skb);
		break;

	case NCI_OP_RF_DISCOVER_RSP:
		nci_rf_disc_rsp_packet(ndev, skb);
		break;

	case NCI_OP_RF_DISCOVER_SELECT_RSP:
		nci_rf_disc_select_rsp_packet(ndev, skb);
		break;

	case NCI_OP_RF_DEACTIVATE_RSP:
		nci_rf_deactivate_rsp_packet(ndev, skb);
		break;

	case NCI_OP_NFCEE_DISCOVER_RSP:
		nci_nfcee_discover_rsp_packet(ndev, skb);
		break;

	case NCI_OP_NFCEE_MODE_SET_RSP:
		nci_nfcee_mode_set_rsp_packet(ndev, skb);
		break;

	default:
		pr_err("unknown rsp opcode 0x%x\n", rsp_opcode);
		break;
	}

	nci_core_rsp_packet(ndev, rsp_opcode, skb);
end:
	kfree_skb(skb);

	/* trigger the next cmd */
	atomic_set(&ndev->cmd_cnt, 1);
	if (!skb_queue_empty(&ndev->cmd_q))
		queue_work(ndev->cmd_wq, &ndev->cmd_work);
}