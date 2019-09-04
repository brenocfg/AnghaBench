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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_rp_read_info {int /*<<< orphan*/  short_name; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_class; void* current_settings; void* supported_settings; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  version; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  short_name; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  hci_ver; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_READ_INFO ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_settings (struct hci_dev*) ; 
 int /*<<< orphan*/  get_supported_settings (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_read_info*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_read_info*,int) ; 

__attribute__((used)) static int read_controller_info(struct sock *sk, struct hci_dev *hdev,
				void *data, u16 data_len)
{
	struct mgmt_rp_read_info rp;

	BT_DBG("sock %p %s", sk, hdev->name);

	hci_dev_lock(hdev);

	memset(&rp, 0, sizeof(rp));

	bacpy(&rp.bdaddr, &hdev->bdaddr);

	rp.version = hdev->hci_ver;
	rp.manufacturer = cpu_to_le16(hdev->manufacturer);

	rp.supported_settings = cpu_to_le32(get_supported_settings(hdev));
	rp.current_settings = cpu_to_le32(get_current_settings(hdev));

	memcpy(rp.dev_class, hdev->dev_class, 3);

	memcpy(rp.name, hdev->dev_name, sizeof(hdev->dev_name));
	memcpy(rp.short_name, hdev->short_name, sizeof(hdev->short_name));

	hci_dev_unlock(hdev);

	return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_INFO, 0, &rp,
				 sizeof(rp));
}