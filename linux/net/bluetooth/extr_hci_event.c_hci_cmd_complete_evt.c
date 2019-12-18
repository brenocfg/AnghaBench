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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct hci_ev_cmd_complete {scalar_t__ ncmd; int /*<<< orphan*/  opcode; } ;
struct hci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  hci_req_complete_t ;
typedef  int /*<<< orphan*/  hci_req_complete_skb_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CMD_PENDING ; 
#define  HCI_OP_DELETE_STORED_LINK_KEY 208 
#define  HCI_OP_EXIT_PERIODIC_INQ 207 
#define  HCI_OP_INQUIRY_CANCEL 206 
#define  HCI_OP_LE_ADD_TO_RESOLV_LIST 205 
#define  HCI_OP_LE_ADD_TO_WHITE_LIST 204 
#define  HCI_OP_LE_CLEAR_RESOLV_LIST 203 
#define  HCI_OP_LE_CLEAR_WHITE_LIST 202 
#define  HCI_OP_LE_DEL_FROM_RESOLV_LIST 201 
#define  HCI_OP_LE_DEL_FROM_WHITE_LIST 200 
#define  HCI_OP_LE_READ_ADV_TX_POWER 199 
#define  HCI_OP_LE_READ_BUFFER_SIZE 198 
#define  HCI_OP_LE_READ_DEF_DATA_LEN 197 
#define  HCI_OP_LE_READ_LOCAL_FEATURES 196 
#define  HCI_OP_LE_READ_MAX_DATA_LEN 195 
#define  HCI_OP_LE_READ_NUM_SUPPORTED_ADV_SETS 194 
#define  HCI_OP_LE_READ_RESOLV_LIST_SIZE 193 
#define  HCI_OP_LE_READ_SUPPORTED_STATES 192 
#define  HCI_OP_LE_READ_WHITE_LIST_SIZE 191 
#define  HCI_OP_LE_SET_ADDR_RESOLV_ENABLE 190 
#define  HCI_OP_LE_SET_ADV_ENABLE 189 
#define  HCI_OP_LE_SET_ADV_PARAM 188 
#define  HCI_OP_LE_SET_ADV_SET_RAND_ADDR 187 
#define  HCI_OP_LE_SET_DEFAULT_PHY 186 
#define  HCI_OP_LE_SET_EXT_ADV_ENABLE 185 
#define  HCI_OP_LE_SET_EXT_ADV_PARAMS 184 
#define  HCI_OP_LE_SET_EXT_SCAN_ENABLE 183 
#define  HCI_OP_LE_SET_EXT_SCAN_PARAMS 182 
#define  HCI_OP_LE_SET_RANDOM_ADDR 181 
#define  HCI_OP_LE_SET_SCAN_ENABLE 180 
#define  HCI_OP_LE_SET_SCAN_PARAM 179 
#define  HCI_OP_LE_WRITE_DEF_DATA_LEN 178 
 int /*<<< orphan*/  HCI_OP_NOP ; 
#define  HCI_OP_PERIODIC_INQ 177 
#define  HCI_OP_PIN_CODE_NEG_REPLY 176 
#define  HCI_OP_PIN_CODE_REPLY 175 
#define  HCI_OP_READ_AUTH_PAYLOAD_TO 174 
#define  HCI_OP_READ_BD_ADDR 173 
#define  HCI_OP_READ_BUFFER_SIZE 172 
#define  HCI_OP_READ_CLASS_OF_DEV 171 
#define  HCI_OP_READ_CLOCK 170 
#define  HCI_OP_READ_DATA_BLOCK_SIZE 169 
#define  HCI_OP_READ_DEF_LINK_POLICY 168 
#define  HCI_OP_READ_FLOW_CONTROL_MODE 167 
#define  HCI_OP_READ_INQ_RSP_TX_POWER 166 
#define  HCI_OP_READ_LINK_POLICY 165 
#define  HCI_OP_READ_LOCAL_AMP_INFO 164 
#define  HCI_OP_READ_LOCAL_COMMANDS 163 
#define  HCI_OP_READ_LOCAL_EXT_FEATURES 162 
#define  HCI_OP_READ_LOCAL_FEATURES 161 
#define  HCI_OP_READ_LOCAL_NAME 160 
#define  HCI_OP_READ_LOCAL_OOB_DATA 159 
#define  HCI_OP_READ_LOCAL_OOB_EXT_DATA 158 
#define  HCI_OP_READ_LOCAL_VERSION 157 
#define  HCI_OP_READ_NUM_SUPPORTED_IAC 156 
#define  HCI_OP_READ_PAGE_SCAN_ACTIVITY 155 
#define  HCI_OP_READ_PAGE_SCAN_TYPE 154 
#define  HCI_OP_READ_RSSI 153 
#define  HCI_OP_READ_STORED_LINK_KEY 152 
#define  HCI_OP_READ_TX_POWER 151 
#define  HCI_OP_READ_VOICE_SETTING 150 
#define  HCI_OP_REMOTE_NAME_REQ_CANCEL 149 
#define  HCI_OP_RESET 148 
#define  HCI_OP_ROLE_DISCOVERY 147 
#define  HCI_OP_USER_CONFIRM_NEG_REPLY 146 
#define  HCI_OP_USER_CONFIRM_REPLY 145 
#define  HCI_OP_USER_PASSKEY_NEG_REPLY 144 
#define  HCI_OP_USER_PASSKEY_REPLY 143 
#define  HCI_OP_WRITE_AUTH_ENABLE 142 
#define  HCI_OP_WRITE_AUTH_PAYLOAD_TO 141 
#define  HCI_OP_WRITE_CLASS_OF_DEV 140 
#define  HCI_OP_WRITE_DEF_LINK_POLICY 139 
#define  HCI_OP_WRITE_ENCRYPT_MODE 138 
#define  HCI_OP_WRITE_LE_HOST_SUPPORTED 137 
#define  HCI_OP_WRITE_LINK_POLICY 136 
#define  HCI_OP_WRITE_LOCAL_NAME 135 
#define  HCI_OP_WRITE_PAGE_SCAN_ACTIVITY 134 
#define  HCI_OP_WRITE_PAGE_SCAN_TYPE 133 
#define  HCI_OP_WRITE_SCAN_ENABLE 132 
#define  HCI_OP_WRITE_SC_SUPPORT 131 
#define  HCI_OP_WRITE_SSP_DEBUG_MODE 130 
#define  HCI_OP_WRITE_SSP_MODE 129 
#define  HCI_OP_WRITE_VOICE_SETTING 128 
 int /*<<< orphan*/  HCI_RESET ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_cc_delete_stored_link_key (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_exit_periodic_inq (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_inquiry_cancel (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_add_to_resolv_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_add_to_white_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_clear_resolv_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_clear_white_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_del_from_resolv_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_del_from_white_list (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_adv_tx_power (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_buffer_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_def_data_len (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_local_features (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_max_data_len (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_num_adv_sets (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_resolv_list_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_supported_states (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_read_white_list_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_addr_resolution_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_adv_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_adv_set_random_addr (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_default_phy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_ext_adv_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_ext_scan_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_ext_scan_param (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_random_addr (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_scan_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_set_scan_param (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_le_write_def_data_len (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_periodic_inq (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_pin_code_neg_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_pin_code_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_auth_payload_timeout (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_bd_addr (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_buffer_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_class_of_dev (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_clock (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_data_block_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_def_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_flow_control_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_inq_rsp_tx_power (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_amp_info (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_commands (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_ext_features (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_features (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_name (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_oob_data (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_oob_ext_data (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_version (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_num_supported_iac (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_page_scan_activity (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_page_scan_type (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_rssi (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_stored_link_key (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_tx_power (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_voice_setting (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_remote_name_req_cancel (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_reset (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_role_discovery (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_set_adv_param (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_set_ext_adv_param (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_user_confirm_neg_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_user_confirm_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_user_passkey_neg_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_user_passkey_reply (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_auth_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_auth_payload_timeout (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_class_of_dev (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_def_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_encrypt_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_le_host_supported (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_local_name (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_page_scan_activity (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_page_scan_type (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_sc_support (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_scan_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_ssp_debug_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_ssp_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_voice_setting (struct hci_dev*,struct sk_buff*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_cmd_complete (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_cmd_complete_evt(struct hci_dev *hdev, struct sk_buff *skb,
				 u16 *opcode, u8 *status,
				 hci_req_complete_t *req_complete,
				 hci_req_complete_skb_t *req_complete_skb)
{
	struct hci_ev_cmd_complete *ev = (void *) skb->data;

	*opcode = __le16_to_cpu(ev->opcode);
	*status = skb->data[sizeof(*ev)];

	skb_pull(skb, sizeof(*ev));

	switch (*opcode) {
	case HCI_OP_INQUIRY_CANCEL:
		hci_cc_inquiry_cancel(hdev, skb);
		break;

	case HCI_OP_PERIODIC_INQ:
		hci_cc_periodic_inq(hdev, skb);
		break;

	case HCI_OP_EXIT_PERIODIC_INQ:
		hci_cc_exit_periodic_inq(hdev, skb);
		break;

	case HCI_OP_REMOTE_NAME_REQ_CANCEL:
		hci_cc_remote_name_req_cancel(hdev, skb);
		break;

	case HCI_OP_ROLE_DISCOVERY:
		hci_cc_role_discovery(hdev, skb);
		break;

	case HCI_OP_READ_LINK_POLICY:
		hci_cc_read_link_policy(hdev, skb);
		break;

	case HCI_OP_WRITE_LINK_POLICY:
		hci_cc_write_link_policy(hdev, skb);
		break;

	case HCI_OP_READ_DEF_LINK_POLICY:
		hci_cc_read_def_link_policy(hdev, skb);
		break;

	case HCI_OP_WRITE_DEF_LINK_POLICY:
		hci_cc_write_def_link_policy(hdev, skb);
		break;

	case HCI_OP_RESET:
		hci_cc_reset(hdev, skb);
		break;

	case HCI_OP_READ_STORED_LINK_KEY:
		hci_cc_read_stored_link_key(hdev, skb);
		break;

	case HCI_OP_DELETE_STORED_LINK_KEY:
		hci_cc_delete_stored_link_key(hdev, skb);
		break;

	case HCI_OP_WRITE_LOCAL_NAME:
		hci_cc_write_local_name(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_NAME:
		hci_cc_read_local_name(hdev, skb);
		break;

	case HCI_OP_WRITE_AUTH_ENABLE:
		hci_cc_write_auth_enable(hdev, skb);
		break;

	case HCI_OP_WRITE_ENCRYPT_MODE:
		hci_cc_write_encrypt_mode(hdev, skb);
		break;

	case HCI_OP_WRITE_SCAN_ENABLE:
		hci_cc_write_scan_enable(hdev, skb);
		break;

	case HCI_OP_READ_CLASS_OF_DEV:
		hci_cc_read_class_of_dev(hdev, skb);
		break;

	case HCI_OP_WRITE_CLASS_OF_DEV:
		hci_cc_write_class_of_dev(hdev, skb);
		break;

	case HCI_OP_READ_VOICE_SETTING:
		hci_cc_read_voice_setting(hdev, skb);
		break;

	case HCI_OP_WRITE_VOICE_SETTING:
		hci_cc_write_voice_setting(hdev, skb);
		break;

	case HCI_OP_READ_NUM_SUPPORTED_IAC:
		hci_cc_read_num_supported_iac(hdev, skb);
		break;

	case HCI_OP_WRITE_SSP_MODE:
		hci_cc_write_ssp_mode(hdev, skb);
		break;

	case HCI_OP_WRITE_SC_SUPPORT:
		hci_cc_write_sc_support(hdev, skb);
		break;

	case HCI_OP_READ_AUTH_PAYLOAD_TO:
		hci_cc_read_auth_payload_timeout(hdev, skb);
		break;

	case HCI_OP_WRITE_AUTH_PAYLOAD_TO:
		hci_cc_write_auth_payload_timeout(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_VERSION:
		hci_cc_read_local_version(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_COMMANDS:
		hci_cc_read_local_commands(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_FEATURES:
		hci_cc_read_local_features(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_EXT_FEATURES:
		hci_cc_read_local_ext_features(hdev, skb);
		break;

	case HCI_OP_READ_BUFFER_SIZE:
		hci_cc_read_buffer_size(hdev, skb);
		break;

	case HCI_OP_READ_BD_ADDR:
		hci_cc_read_bd_addr(hdev, skb);
		break;

	case HCI_OP_READ_PAGE_SCAN_ACTIVITY:
		hci_cc_read_page_scan_activity(hdev, skb);
		break;

	case HCI_OP_WRITE_PAGE_SCAN_ACTIVITY:
		hci_cc_write_page_scan_activity(hdev, skb);
		break;

	case HCI_OP_READ_PAGE_SCAN_TYPE:
		hci_cc_read_page_scan_type(hdev, skb);
		break;

	case HCI_OP_WRITE_PAGE_SCAN_TYPE:
		hci_cc_write_page_scan_type(hdev, skb);
		break;

	case HCI_OP_READ_DATA_BLOCK_SIZE:
		hci_cc_read_data_block_size(hdev, skb);
		break;

	case HCI_OP_READ_FLOW_CONTROL_MODE:
		hci_cc_read_flow_control_mode(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_AMP_INFO:
		hci_cc_read_local_amp_info(hdev, skb);
		break;

	case HCI_OP_READ_CLOCK:
		hci_cc_read_clock(hdev, skb);
		break;

	case HCI_OP_READ_INQ_RSP_TX_POWER:
		hci_cc_read_inq_rsp_tx_power(hdev, skb);
		break;

	case HCI_OP_PIN_CODE_REPLY:
		hci_cc_pin_code_reply(hdev, skb);
		break;

	case HCI_OP_PIN_CODE_NEG_REPLY:
		hci_cc_pin_code_neg_reply(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_OOB_DATA:
		hci_cc_read_local_oob_data(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_OOB_EXT_DATA:
		hci_cc_read_local_oob_ext_data(hdev, skb);
		break;

	case HCI_OP_LE_READ_BUFFER_SIZE:
		hci_cc_le_read_buffer_size(hdev, skb);
		break;

	case HCI_OP_LE_READ_LOCAL_FEATURES:
		hci_cc_le_read_local_features(hdev, skb);
		break;

	case HCI_OP_LE_READ_ADV_TX_POWER:
		hci_cc_le_read_adv_tx_power(hdev, skb);
		break;

	case HCI_OP_USER_CONFIRM_REPLY:
		hci_cc_user_confirm_reply(hdev, skb);
		break;

	case HCI_OP_USER_CONFIRM_NEG_REPLY:
		hci_cc_user_confirm_neg_reply(hdev, skb);
		break;

	case HCI_OP_USER_PASSKEY_REPLY:
		hci_cc_user_passkey_reply(hdev, skb);
		break;

	case HCI_OP_USER_PASSKEY_NEG_REPLY:
		hci_cc_user_passkey_neg_reply(hdev, skb);
		break;

	case HCI_OP_LE_SET_RANDOM_ADDR:
		hci_cc_le_set_random_addr(hdev, skb);
		break;

	case HCI_OP_LE_SET_ADV_ENABLE:
		hci_cc_le_set_adv_enable(hdev, skb);
		break;

	case HCI_OP_LE_SET_SCAN_PARAM:
		hci_cc_le_set_scan_param(hdev, skb);
		break;

	case HCI_OP_LE_SET_SCAN_ENABLE:
		hci_cc_le_set_scan_enable(hdev, skb);
		break;

	case HCI_OP_LE_READ_WHITE_LIST_SIZE:
		hci_cc_le_read_white_list_size(hdev, skb);
		break;

	case HCI_OP_LE_CLEAR_WHITE_LIST:
		hci_cc_le_clear_white_list(hdev, skb);
		break;

	case HCI_OP_LE_ADD_TO_WHITE_LIST:
		hci_cc_le_add_to_white_list(hdev, skb);
		break;

	case HCI_OP_LE_DEL_FROM_WHITE_LIST:
		hci_cc_le_del_from_white_list(hdev, skb);
		break;

	case HCI_OP_LE_READ_SUPPORTED_STATES:
		hci_cc_le_read_supported_states(hdev, skb);
		break;

	case HCI_OP_LE_READ_DEF_DATA_LEN:
		hci_cc_le_read_def_data_len(hdev, skb);
		break;

	case HCI_OP_LE_WRITE_DEF_DATA_LEN:
		hci_cc_le_write_def_data_len(hdev, skb);
		break;

	case HCI_OP_LE_ADD_TO_RESOLV_LIST:
		hci_cc_le_add_to_resolv_list(hdev, skb);
		break;

	case HCI_OP_LE_DEL_FROM_RESOLV_LIST:
		hci_cc_le_del_from_resolv_list(hdev, skb);
		break;

	case HCI_OP_LE_CLEAR_RESOLV_LIST:
		hci_cc_le_clear_resolv_list(hdev, skb);
		break;

	case HCI_OP_LE_READ_RESOLV_LIST_SIZE:
		hci_cc_le_read_resolv_list_size(hdev, skb);
		break;

	case HCI_OP_LE_SET_ADDR_RESOLV_ENABLE:
		hci_cc_le_set_addr_resolution_enable(hdev, skb);
		break;

	case HCI_OP_LE_READ_MAX_DATA_LEN:
		hci_cc_le_read_max_data_len(hdev, skb);
		break;

	case HCI_OP_WRITE_LE_HOST_SUPPORTED:
		hci_cc_write_le_host_supported(hdev, skb);
		break;

	case HCI_OP_LE_SET_ADV_PARAM:
		hci_cc_set_adv_param(hdev, skb);
		break;

	case HCI_OP_READ_RSSI:
		hci_cc_read_rssi(hdev, skb);
		break;

	case HCI_OP_READ_TX_POWER:
		hci_cc_read_tx_power(hdev, skb);
		break;

	case HCI_OP_WRITE_SSP_DEBUG_MODE:
		hci_cc_write_ssp_debug_mode(hdev, skb);
		break;

	case HCI_OP_LE_SET_EXT_SCAN_PARAMS:
		hci_cc_le_set_ext_scan_param(hdev, skb);
		break;

	case HCI_OP_LE_SET_EXT_SCAN_ENABLE:
		hci_cc_le_set_ext_scan_enable(hdev, skb);
		break;

	case HCI_OP_LE_SET_DEFAULT_PHY:
		hci_cc_le_set_default_phy(hdev, skb);
		break;

	case HCI_OP_LE_READ_NUM_SUPPORTED_ADV_SETS:
		hci_cc_le_read_num_adv_sets(hdev, skb);
		break;

	case HCI_OP_LE_SET_EXT_ADV_PARAMS:
		hci_cc_set_ext_adv_param(hdev, skb);
		break;

	case HCI_OP_LE_SET_EXT_ADV_ENABLE:
		hci_cc_le_set_ext_adv_enable(hdev, skb);
		break;

	case HCI_OP_LE_SET_ADV_SET_RAND_ADDR:
		hci_cc_le_set_adv_set_random_addr(hdev, skb);
		break;

	default:
		BT_DBG("%s opcode 0x%4.4x", hdev->name, *opcode);
		break;
	}

	if (*opcode != HCI_OP_NOP)
		cancel_delayed_work(&hdev->cmd_timer);

	if (ev->ncmd && !test_bit(HCI_RESET, &hdev->flags))
		atomic_set(&hdev->cmd_cnt, 1);

	hci_req_cmd_complete(hdev, *opcode, *status, req_complete,
			     req_complete_skb);

	if (hci_dev_test_flag(hdev, HCI_CMD_PENDING)) {
		bt_dev_err(hdev,
			   "unexpected event for opcode 0x%4.4x", *opcode);
		return;
	}

	if (atomic_read(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_work(hdev->workqueue, &hdev->cmd_work);
}