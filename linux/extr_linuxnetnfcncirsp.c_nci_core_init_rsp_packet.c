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
struct nci_dev {scalar_t__ nfcc_features; scalar_t__ num_supported_rf_interfaces; scalar_t__* supported_rf_interfaces; scalar_t__ max_logical_connections; scalar_t__ max_routing_table_size; scalar_t__ max_ctrl_pkt_payload_len; scalar_t__ max_size_for_large_params; scalar_t__ manufact_id; scalar_t__ manufact_specific_info; } ;
struct nci_core_init_rsp_2 {scalar_t__ max_logical_connections; scalar_t__ max_ctrl_pkt_payload_len; scalar_t__ manufact_id; int /*<<< orphan*/  manufact_specific_info; int /*<<< orphan*/  max_size_for_large_params; int /*<<< orphan*/  max_routing_table_size; } ;
struct nci_core_init_rsp_1 {scalar_t__ status; scalar_t__ num_supported_rf_interfaces; int /*<<< orphan*/  supported_rf_interfaces; int /*<<< orphan*/  nfcc_features; } ;

/* Variables and functions */
 scalar_t__ NCI_MAX_SUPPORTED_RF_INTERFACES ; 
 scalar_t__ NCI_STATUS_OK ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static void nci_core_init_rsp_packet(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct nci_core_init_rsp_1 *rsp_1 = (void *) skb->data;
	struct nci_core_init_rsp_2 *rsp_2;

	pr_debug("status 0x%x\n", rsp_1->status);

	if (rsp_1->status != NCI_STATUS_OK)
		goto exit;

	ndev->nfcc_features = __le32_to_cpu(rsp_1->nfcc_features);
	ndev->num_supported_rf_interfaces = rsp_1->num_supported_rf_interfaces;

	if (ndev->num_supported_rf_interfaces >
	    NCI_MAX_SUPPORTED_RF_INTERFACES) {
		ndev->num_supported_rf_interfaces =
			NCI_MAX_SUPPORTED_RF_INTERFACES;
	}

	memcpy(ndev->supported_rf_interfaces,
	       rsp_1->supported_rf_interfaces,
	       ndev->num_supported_rf_interfaces);

	rsp_2 = (void *) (skb->data + 6 + rsp_1->num_supported_rf_interfaces);

	ndev->max_logical_connections = rsp_2->max_logical_connections;
	ndev->max_routing_table_size =
		__le16_to_cpu(rsp_2->max_routing_table_size);
	ndev->max_ctrl_pkt_payload_len =
		rsp_2->max_ctrl_pkt_payload_len;
	ndev->max_size_for_large_params =
		__le16_to_cpu(rsp_2->max_size_for_large_params);
	ndev->manufact_id =
		rsp_2->manufact_id;
	ndev->manufact_specific_info =
		__le32_to_cpu(rsp_2->manufact_specific_info);

	pr_debug("nfcc_features 0x%x\n",
		 ndev->nfcc_features);
	pr_debug("num_supported_rf_interfaces %d\n",
		 ndev->num_supported_rf_interfaces);
	pr_debug("supported_rf_interfaces[0] 0x%x\n",
		 ndev->supported_rf_interfaces[0]);
	pr_debug("supported_rf_interfaces[1] 0x%x\n",
		 ndev->supported_rf_interfaces[1]);
	pr_debug("supported_rf_interfaces[2] 0x%x\n",
		 ndev->supported_rf_interfaces[2]);
	pr_debug("supported_rf_interfaces[3] 0x%x\n",
		 ndev->supported_rf_interfaces[3]);
	pr_debug("max_logical_connections %d\n",
		 ndev->max_logical_connections);
	pr_debug("max_routing_table_size %d\n",
		 ndev->max_routing_table_size);
	pr_debug("max_ctrl_pkt_payload_len %d\n",
		 ndev->max_ctrl_pkt_payload_len);
	pr_debug("max_size_for_large_params %d\n",
		 ndev->max_size_for_large_params);
	pr_debug("manufact_id 0x%x\n",
		 ndev->manufact_id);
	pr_debug("manufact_specific_info 0x%x\n",
		 ndev->manufact_specific_info);

exit:
	nci_req_complete(ndev, rsp_1->status);
}