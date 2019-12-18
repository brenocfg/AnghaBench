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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct hci_dev {int pkt_type; int num_iac; int io_capability; int manufacturer; int cur_adv_instance; int sniff_max_interval; int sniff_min_interval; int le_adv_channel_map; int le_adv_min_interval; int le_adv_max_interval; int le_scan_interval; int le_scan_window; int le_conn_min_interval; int le_conn_max_interval; int le_conn_latency; int le_supv_timeout; int le_def_tx_len; int le_def_tx_time; int le_max_tx_len; int le_max_tx_time; int le_max_rx_len; int le_max_rx_time; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  req_wait_q; int /*<<< orphan*/  raw_q; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  power_off; int /*<<< orphan*/  error_reset; int /*<<< orphan*/  power_on; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  adv_instances; TYPE_1__ conn_hash; int /*<<< orphan*/  pend_le_reports; int /*<<< orphan*/  pend_le_conns; int /*<<< orphan*/  le_conn_params; int /*<<< orphan*/  le_resolv_list; int /*<<< orphan*/  le_white_list; int /*<<< orphan*/  remote_oob_data; int /*<<< orphan*/  identity_resolving_keys; int /*<<< orphan*/  long_term_keys; int /*<<< orphan*/  link_keys; int /*<<< orphan*/  uuids; int /*<<< orphan*/  whitelist; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  mgmt_pending; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  min_enc_key_size; int /*<<< orphan*/  auth_payload_timeout; int /*<<< orphan*/  conn_info_max_age; int /*<<< orphan*/  conn_info_min_age; int /*<<< orphan*/  discov_interleaved_timeout; int /*<<< orphan*/  rpa_timeout; int /*<<< orphan*/  le_num_of_adv_sets; void* le_rx_def_phys; void* le_tx_def_phys; int /*<<< orphan*/  le_min_key_size; int /*<<< orphan*/  le_max_key_size; scalar_t__ adv_instance_timeout; scalar_t__ adv_instance_cnt; void* adv_tx_power; void* inq_tx_power; int /*<<< orphan*/  link_mode; int /*<<< orphan*/  esco_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_AUTH_PAYLOAD_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_CONN_INFO_MAX_AGE ; 
 int /*<<< orphan*/  DEFAULT_CONN_INFO_MIN_AGE ; 
 int /*<<< orphan*/  DISCOV_INTERLEAVED_TIMEOUT ; 
 int /*<<< orphan*/  ESCO_HV1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_DEFAULT_RPA_TIMEOUT ; 
 int HCI_DH1 ; 
 int HCI_DM1 ; 
 int HCI_HV1 ; 
 void* HCI_LE_SET_PHY_1M ; 
 int /*<<< orphan*/  HCI_LM_ACCEPT ; 
 int /*<<< orphan*/  HCI_MAX_ADV_INSTANCES ; 
 int /*<<< orphan*/  HCI_MIN_ENC_KEY_SIZE ; 
 void* HCI_TX_POWER_INVALID ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_MAX_ENC_KEY_SIZE ; 
 int /*<<< orphan*/  SMP_MIN_ENC_KEY_SIZE ; 
 int /*<<< orphan*/  discovery_init (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_cmd_timeout ; 
 int /*<<< orphan*/  hci_cmd_work ; 
 int /*<<< orphan*/  hci_error_reset ; 
 int /*<<< orphan*/  hci_init_sysfs (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_power_off ; 
 int /*<<< orphan*/  hci_power_on ; 
 int /*<<< orphan*/  hci_request_setup (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_rx_work ; 
 int /*<<< orphan*/  hci_tx_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct hci_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

struct hci_dev *hci_alloc_dev(void)
{
	struct hci_dev *hdev;

	hdev = kzalloc(sizeof(*hdev), GFP_KERNEL);
	if (!hdev)
		return NULL;

	hdev->pkt_type  = (HCI_DM1 | HCI_DH1 | HCI_HV1);
	hdev->esco_type = (ESCO_HV1);
	hdev->link_mode = (HCI_LM_ACCEPT);
	hdev->num_iac = 0x01;		/* One IAC support is mandatory */
	hdev->io_capability = 0x03;	/* No Input No Output */
	hdev->manufacturer = 0xffff;	/* Default to internal use */
	hdev->inq_tx_power = HCI_TX_POWER_INVALID;
	hdev->adv_tx_power = HCI_TX_POWER_INVALID;
	hdev->adv_instance_cnt = 0;
	hdev->cur_adv_instance = 0x00;
	hdev->adv_instance_timeout = 0;

	hdev->sniff_max_interval = 800;
	hdev->sniff_min_interval = 80;

	hdev->le_adv_channel_map = 0x07;
	hdev->le_adv_min_interval = 0x0800;
	hdev->le_adv_max_interval = 0x0800;
	hdev->le_scan_interval = 0x0060;
	hdev->le_scan_window = 0x0030;
	hdev->le_conn_min_interval = 0x0018;
	hdev->le_conn_max_interval = 0x0028;
	hdev->le_conn_latency = 0x0000;
	hdev->le_supv_timeout = 0x002a;
	hdev->le_def_tx_len = 0x001b;
	hdev->le_def_tx_time = 0x0148;
	hdev->le_max_tx_len = 0x001b;
	hdev->le_max_tx_time = 0x0148;
	hdev->le_max_rx_len = 0x001b;
	hdev->le_max_rx_time = 0x0148;
	hdev->le_max_key_size = SMP_MAX_ENC_KEY_SIZE;
	hdev->le_min_key_size = SMP_MIN_ENC_KEY_SIZE;
	hdev->le_tx_def_phys = HCI_LE_SET_PHY_1M;
	hdev->le_rx_def_phys = HCI_LE_SET_PHY_1M;
	hdev->le_num_of_adv_sets = HCI_MAX_ADV_INSTANCES;

	hdev->rpa_timeout = HCI_DEFAULT_RPA_TIMEOUT;
	hdev->discov_interleaved_timeout = DISCOV_INTERLEAVED_TIMEOUT;
	hdev->conn_info_min_age = DEFAULT_CONN_INFO_MIN_AGE;
	hdev->conn_info_max_age = DEFAULT_CONN_INFO_MAX_AGE;
	hdev->auth_payload_timeout = DEFAULT_AUTH_PAYLOAD_TIMEOUT;
	hdev->min_enc_key_size = HCI_MIN_ENC_KEY_SIZE;

	mutex_init(&hdev->lock);
	mutex_init(&hdev->req_lock);

	INIT_LIST_HEAD(&hdev->mgmt_pending);
	INIT_LIST_HEAD(&hdev->blacklist);
	INIT_LIST_HEAD(&hdev->whitelist);
	INIT_LIST_HEAD(&hdev->uuids);
	INIT_LIST_HEAD(&hdev->link_keys);
	INIT_LIST_HEAD(&hdev->long_term_keys);
	INIT_LIST_HEAD(&hdev->identity_resolving_keys);
	INIT_LIST_HEAD(&hdev->remote_oob_data);
	INIT_LIST_HEAD(&hdev->le_white_list);
	INIT_LIST_HEAD(&hdev->le_resolv_list);
	INIT_LIST_HEAD(&hdev->le_conn_params);
	INIT_LIST_HEAD(&hdev->pend_le_conns);
	INIT_LIST_HEAD(&hdev->pend_le_reports);
	INIT_LIST_HEAD(&hdev->conn_hash.list);
	INIT_LIST_HEAD(&hdev->adv_instances);

	INIT_WORK(&hdev->rx_work, hci_rx_work);
	INIT_WORK(&hdev->cmd_work, hci_cmd_work);
	INIT_WORK(&hdev->tx_work, hci_tx_work);
	INIT_WORK(&hdev->power_on, hci_power_on);
	INIT_WORK(&hdev->error_reset, hci_error_reset);

	INIT_DELAYED_WORK(&hdev->power_off, hci_power_off);

	skb_queue_head_init(&hdev->rx_q);
	skb_queue_head_init(&hdev->cmd_q);
	skb_queue_head_init(&hdev->raw_q);

	init_waitqueue_head(&hdev->req_wait_q);

	INIT_DELAYED_WORK(&hdev->cmd_timer, hci_cmd_timeout);

	hci_request_setup(hdev);

	hci_init_sysfs(hdev);
	discovery_init(hdev);

	return hdev;
}