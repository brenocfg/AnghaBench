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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct mgmt_rp_read_ext_info {void* eir_len; int /*<<< orphan*/  eir; void* current_settings; void* supported_settings; void* manufacturer; int /*<<< orphan*/  version; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  id; scalar_t__ manufacturer; int /*<<< orphan*/  hci_ver; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MGMT_DEV_CLASS_EVENTS ; 
 int /*<<< orphan*/  HCI_MGMT_EXT_INFO_EVENTS ; 
 int /*<<< orphan*/  HCI_MGMT_LOCAL_NAME_EVENTS ; 
 int /*<<< orphan*/  MGMT_OP_READ_EXT_INFO ; 
 scalar_t__ append_eir_data_to_buf (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_settings (struct hci_dev*) ; 
 int /*<<< orphan*/  get_supported_settings (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sock_clear_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_read_ext_info*,scalar_t__) ; 

__attribute__((used)) static int read_ext_controller_info(struct sock *sk, struct hci_dev *hdev,
				    void *data, u16 data_len)
{
	char buf[512];
	struct mgmt_rp_read_ext_info *rp = (void *)buf;
	u16 eir_len;

	BT_DBG("sock %p %s", sk, hdev->name);

	memset(&buf, 0, sizeof(buf));

	hci_dev_lock(hdev);

	bacpy(&rp->bdaddr, &hdev->bdaddr);

	rp->version = hdev->hci_ver;
	rp->manufacturer = cpu_to_le16(hdev->manufacturer);

	rp->supported_settings = cpu_to_le32(get_supported_settings(hdev));
	rp->current_settings = cpu_to_le32(get_current_settings(hdev));


	eir_len = append_eir_data_to_buf(hdev, rp->eir);
	rp->eir_len = cpu_to_le16(eir_len);

	hci_dev_unlock(hdev);

	/* If this command is called at least once, then the events
	 * for class of device and local name changes are disabled
	 * and only the new extended controller information event
	 * is used.
	 */
	hci_sock_set_flag(sk, HCI_MGMT_EXT_INFO_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_DEV_CLASS_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_LOCAL_NAME_EVENTS);

	return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_EXT_INFO, 0, rp,
				 sizeof(*rp) + eir_len);
}