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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nxp_nci_fw_info {int /*<<< orphan*/  work; scalar_t__ fw; int /*<<< orphan*/  cmd_result; int /*<<< orphan*/  cmd_completion; } ;
struct nxp_nci_info {struct nxp_nci_fw_info fw_info; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NXP_NCI_FW_HDR_LEN ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nxp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int nxp_nci_fw_check_crc (struct sk_buff*) ; 
 int /*<<< orphan*/  nxp_nci_fw_read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

void nxp_nci_fw_recv_frame(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct nxp_nci_info *info = nci_get_drvdata(ndev);
	struct nxp_nci_fw_info *fw_info = &info->fw_info;

	complete(&fw_info->cmd_completion);

	if (skb) {
		if (nxp_nci_fw_check_crc(skb) != 0x00)
			fw_info->cmd_result = -EBADMSG;
		else
			fw_info->cmd_result = nxp_nci_fw_read_status(*(u8 *)skb_pull(skb, NXP_NCI_FW_HDR_LEN));
		kfree_skb(skb);
	} else {
		fw_info->cmd_result = -EIO;
	}

	if (fw_info->fw)
		schedule_work(&fw_info->work);
}