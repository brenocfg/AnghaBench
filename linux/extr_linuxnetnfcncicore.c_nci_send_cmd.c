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
struct sk_buff {int dummy; } ;
struct nci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  cmd_q; } ;
struct nci_ctrl_hdr {scalar_t__ plen; int /*<<< orphan*/  oid; int /*<<< orphan*/  gid; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NCI_CTRL_HDR_SIZE ; 
 int /*<<< orphan*/  NCI_MT_CMD_PKT ; 
 int /*<<< orphan*/  NCI_PBF_LAST ; 
 int /*<<< orphan*/  nci_mt_set (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_opcode_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_opcode_oid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_pbf_set (scalar_t__*,int /*<<< orphan*/ ) ; 
 struct sk_buff* nci_skb_alloc (struct nci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nci_ctrl_hdr* skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int nci_send_cmd(struct nci_dev *ndev, __u16 opcode, __u8 plen, void *payload)
{
	struct nci_ctrl_hdr *hdr;
	struct sk_buff *skb;

	pr_debug("opcode 0x%x, plen %d\n", opcode, plen);

	skb = nci_skb_alloc(ndev, (NCI_CTRL_HDR_SIZE + plen), GFP_KERNEL);
	if (!skb) {
		pr_err("no memory for command\n");
		return -ENOMEM;
	}

	hdr = skb_put(skb, NCI_CTRL_HDR_SIZE);
	hdr->gid = nci_opcode_gid(opcode);
	hdr->oid = nci_opcode_oid(opcode);
	hdr->plen = plen;

	nci_mt_set((__u8 *)hdr, NCI_MT_CMD_PKT);
	nci_pbf_set((__u8 *)hdr, NCI_PBF_LAST);

	if (plen)
		skb_put_data(skb, payload, plen);

	skb_queue_tail(&ndev->cmd_q, skb);
	queue_work(ndev->cmd_wq, &ndev->cmd_work);

	return 0;
}