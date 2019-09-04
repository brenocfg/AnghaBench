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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_rp_read_config_info {int /*<<< orphan*/  missing_options; int /*<<< orphan*/  supported_options; int /*<<< orphan*/  manufacturer; } ;
struct hci_dev {int /*<<< orphan*/  id; scalar_t__ set_bdaddr; int /*<<< orphan*/  quirks; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_QUIRK_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  MGMT_OPTION_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  MGMT_OPTION_PUBLIC_ADDRESS ; 
 int /*<<< orphan*/  MGMT_OP_READ_CONFIG_INFO ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_missing_options (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_read_config_info*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_read_config_info*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_config_info(struct sock *sk, struct hci_dev *hdev,
			    void *data, u16 data_len)
{
	struct mgmt_rp_read_config_info rp;
	u32 options = 0;

	BT_DBG("sock %p %s", sk, hdev->name);

	hci_dev_lock(hdev);

	memset(&rp, 0, sizeof(rp));
	rp.manufacturer = cpu_to_le16(hdev->manufacturer);

	if (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks))
		options |= MGMT_OPTION_EXTERNAL_CONFIG;

	if (hdev->set_bdaddr)
		options |= MGMT_OPTION_PUBLIC_ADDRESS;

	rp.supported_options = cpu_to_le32(options);
	rp.missing_options = get_missing_options(hdev);

	hci_dev_unlock(hdev);

	return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_CONFIG_INFO, 0,
				 &rp, sizeof(rp));
}