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
struct mgmt_rp_get_phy_confguration {void* configurable_phys; void* selected_phys; void* supported_phys; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_GET_PHY_CONFIGURATION ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_configurable_phys (struct hci_dev*) ; 
 int /*<<< orphan*/  get_selected_phys (struct hci_dev*) ; 
 int /*<<< orphan*/  get_supported_phys (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_get_phy_confguration*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_get_phy_confguration*,int) ; 

__attribute__((used)) static int get_phy_configuration(struct sock *sk, struct hci_dev *hdev,
				 void *data, u16 len)
{
	struct mgmt_rp_get_phy_confguration rp;

	BT_DBG("sock %p %s", sk, hdev->name);

	hci_dev_lock(hdev);

	memset(&rp, 0, sizeof(rp));

	rp.supported_phys = cpu_to_le32(get_supported_phys(hdev));
	rp.selected_phys = cpu_to_le32(get_selected_phys(hdev));
	rp.configurable_phys = cpu_to_le32(get_configurable_phys(hdev));

	hci_dev_unlock(hdev);

	return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_PHY_CONFIGURATION, 0,
				 &rp, sizeof(rp));
}