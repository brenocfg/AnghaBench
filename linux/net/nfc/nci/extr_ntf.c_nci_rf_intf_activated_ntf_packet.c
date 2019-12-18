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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfcf_listen; int /*<<< orphan*/  nfcv_poll; int /*<<< orphan*/  nfcf_poll; int /*<<< orphan*/  nfcb_poll; int /*<<< orphan*/  nfca_poll; } ;
struct nci_rf_intf_activated_ntf {scalar_t__ rf_discovery_id; scalar_t__ rf_interface; scalar_t__ rf_protocol; scalar_t__ activation_rf_tech_and_mode; scalar_t__ max_data_pkt_payload_size; scalar_t__ initial_num_credits; scalar_t__ rf_tech_specific_params_len; scalar_t__ data_exch_rf_tech_and_mode; scalar_t__ data_exch_tx_bit_rate; scalar_t__ data_exch_rx_bit_rate; scalar_t__ activation_params_len; TYPE_1__ rf_tech_specific_params; } ;
struct nci_dev {int /*<<< orphan*/  remote_gb_len; int /*<<< orphan*/  remote_gb; int /*<<< orphan*/  nfc_dev; int /*<<< orphan*/  state; struct nci_conn_info* rf_conn_info; } ;
struct nci_conn_info {scalar_t__ max_pkt_payload_len; scalar_t__ initial_num_credits; int /*<<< orphan*/  credits_cnt; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ NCI_DISCOVERY ; 
 scalar_t__ NCI_LISTEN_ACTIVE ; 
#define  NCI_NFC_A_PASSIVE_LISTEN_MODE 136 
#define  NCI_NFC_A_PASSIVE_POLL_MODE 135 
#define  NCI_NFC_B_PASSIVE_POLL_MODE 134 
#define  NCI_NFC_F_PASSIVE_LISTEN_MODE 133 
#define  NCI_NFC_F_PASSIVE_POLL_MODE 132 
#define  NCI_NFC_V_PASSIVE_POLL_MODE 131 
 scalar_t__ NCI_POLL_ACTIVE ; 
#define  NCI_RF_INTERFACE_FRAME 130 
#define  NCI_RF_INTERFACE_ISO_DEP 129 
 scalar_t__ NCI_RF_INTERFACE_NFCEE_DIRECT ; 
#define  NCI_RF_INTERFACE_NFC_DEP 128 
 scalar_t__ NCI_RF_PROTOCOL_NFC_DEP ; 
 int NCI_RF_TECH_MODE_LISTEN_MASK ; 
 int NCI_STATUS_OK ; 
 int NCI_STATUS_RF_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NFC_COMM_PASSIVE ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP_MASK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int nci_extract_activation_params_iso_dep (struct nci_dev*,struct nci_rf_intf_activated_ntf*,int /*<<< orphan*/ *) ; 
 int nci_extract_activation_params_nfc_dep (struct nci_dev*,struct nci_rf_intf_activated_ntf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nci_extract_rf_params_nfca_passive_poll (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nci_extract_rf_params_nfcb_passive_poll (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nci_extract_rf_params_nfcf_passive_listen (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nci_extract_rf_params_nfcf_passive_poll (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nci_extract_rf_params_nfcv_passive_poll (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int) ; 
 int nci_store_general_bytes_nfc_dep (struct nci_dev*,struct nci_rf_intf_activated_ntf*) ; 
 int /*<<< orphan*/  nci_target_auto_activated (struct nci_dev*,struct nci_rf_intf_activated_ntf*) ; 
 int nfc_tm_activated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void nci_rf_intf_activated_ntf_packet(struct nci_dev *ndev,
					     struct sk_buff *skb)
{
	struct nci_conn_info    *conn_info;
	struct nci_rf_intf_activated_ntf ntf;
	__u8 *data = skb->data;
	int err = NCI_STATUS_OK;

	ntf.rf_discovery_id = *data++;
	ntf.rf_interface = *data++;
	ntf.rf_protocol = *data++;
	ntf.activation_rf_tech_and_mode = *data++;
	ntf.max_data_pkt_payload_size = *data++;
	ntf.initial_num_credits = *data++;
	ntf.rf_tech_specific_params_len = *data++;

	pr_debug("rf_discovery_id %d\n", ntf.rf_discovery_id);
	pr_debug("rf_interface 0x%x\n", ntf.rf_interface);
	pr_debug("rf_protocol 0x%x\n", ntf.rf_protocol);
	pr_debug("activation_rf_tech_and_mode 0x%x\n",
		 ntf.activation_rf_tech_and_mode);
	pr_debug("max_data_pkt_payload_size 0x%x\n",
		 ntf.max_data_pkt_payload_size);
	pr_debug("initial_num_credits 0x%x\n",
		 ntf.initial_num_credits);
	pr_debug("rf_tech_specific_params_len %d\n",
		 ntf.rf_tech_specific_params_len);

	/* If this contains a value of 0x00 (NFCEE Direct RF
	 * Interface) then all following parameters SHALL contain a
	 * value of 0 and SHALL be ignored.
	 */
	if (ntf.rf_interface == NCI_RF_INTERFACE_NFCEE_DIRECT)
		goto listen;

	if (ntf.rf_tech_specific_params_len > 0) {
		switch (ntf.activation_rf_tech_and_mode) {
		case NCI_NFC_A_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfca_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfca_poll), data);
			break;

		case NCI_NFC_B_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcb_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfcb_poll), data);
			break;

		case NCI_NFC_F_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcf_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfcf_poll), data);
			break;

		case NCI_NFC_V_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcv_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfcv_poll), data);
			break;

		case NCI_NFC_A_PASSIVE_LISTEN_MODE:
			/* no RF technology specific parameters */
			break;

		case NCI_NFC_F_PASSIVE_LISTEN_MODE:
			data = nci_extract_rf_params_nfcf_passive_listen(ndev,
				&(ntf.rf_tech_specific_params.nfcf_listen),
				data);
			break;

		default:
			pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
			       ntf.activation_rf_tech_and_mode);
			err = NCI_STATUS_RF_PROTOCOL_ERROR;
			goto exit;
		}
	}

	ntf.data_exch_rf_tech_and_mode = *data++;
	ntf.data_exch_tx_bit_rate = *data++;
	ntf.data_exch_rx_bit_rate = *data++;
	ntf.activation_params_len = *data++;

	pr_debug("data_exch_rf_tech_and_mode 0x%x\n",
		 ntf.data_exch_rf_tech_and_mode);
	pr_debug("data_exch_tx_bit_rate 0x%x\n", ntf.data_exch_tx_bit_rate);
	pr_debug("data_exch_rx_bit_rate 0x%x\n", ntf.data_exch_rx_bit_rate);
	pr_debug("activation_params_len %d\n", ntf.activation_params_len);

	if (ntf.activation_params_len > 0) {
		switch (ntf.rf_interface) {
		case NCI_RF_INTERFACE_ISO_DEP:
			err = nci_extract_activation_params_iso_dep(ndev,
								    &ntf, data);
			break;

		case NCI_RF_INTERFACE_NFC_DEP:
			err = nci_extract_activation_params_nfc_dep(ndev,
								    &ntf, data);
			break;

		case NCI_RF_INTERFACE_FRAME:
			/* no activation params */
			break;

		default:
			pr_err("unsupported rf_interface 0x%x\n",
			       ntf.rf_interface);
			err = NCI_STATUS_RF_PROTOCOL_ERROR;
			break;
		}
	}

exit:
	if (err == NCI_STATUS_OK) {
		conn_info = ndev->rf_conn_info;
		if (!conn_info)
			return;

		conn_info->max_pkt_payload_len = ntf.max_data_pkt_payload_size;
		conn_info->initial_num_credits = ntf.initial_num_credits;

		/* set the available credits to initial value */
		atomic_set(&conn_info->credits_cnt,
			   conn_info->initial_num_credits);

		/* store general bytes to be reported later in dep_link_up */
		if (ntf.rf_interface == NCI_RF_INTERFACE_NFC_DEP) {
			err = nci_store_general_bytes_nfc_dep(ndev, &ntf);
			if (err != NCI_STATUS_OK)
				pr_err("unable to store general bytes\n");
		}
	}

	if (!(ntf.activation_rf_tech_and_mode & NCI_RF_TECH_MODE_LISTEN_MASK)) {
		/* Poll mode */
		if (atomic_read(&ndev->state) == NCI_DISCOVERY) {
			/* A single target was found and activated
			 * automatically */
			atomic_set(&ndev->state, NCI_POLL_ACTIVE);
			if (err == NCI_STATUS_OK)
				nci_target_auto_activated(ndev, &ntf);
		} else {	/* ndev->state == NCI_W4_HOST_SELECT */
			/* A selected target was activated, so complete the
			 * request */
			atomic_set(&ndev->state, NCI_POLL_ACTIVE);
			nci_req_complete(ndev, err);
		}
	} else {
listen:
		/* Listen mode */
		atomic_set(&ndev->state, NCI_LISTEN_ACTIVE);
		if (err == NCI_STATUS_OK &&
		    ntf.rf_protocol == NCI_RF_PROTOCOL_NFC_DEP) {
			err = nfc_tm_activated(ndev->nfc_dev,
					       NFC_PROTO_NFC_DEP_MASK,
					       NFC_COMM_PASSIVE,
					       ndev->remote_gb,
					       ndev->remote_gb_len);
			if (err != NCI_STATUS_OK)
				pr_err("error when signaling tm activation\n");
		}
	}
}