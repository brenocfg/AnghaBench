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
struct l2cap_chan {int dummy; } ;
struct hci_dev {struct l2cap_chan* smp_bredr_data; struct l2cap_chan* smp_data; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_FORCE_BREDR_SMP ; 
 scalar_t__ IS_ERR (struct l2cap_chan*) ; 
 int /*<<< orphan*/  L2CAP_CID_SMP ; 
 int /*<<< orphan*/  L2CAP_CID_SMP_BREDR ; 
 int PTR_ERR (struct l2cap_chan*) ; 
 scalar_t__ WARN_ON (struct l2cap_chan*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  force_bredr_smp_fops ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_max_key_size_fops ; 
 int /*<<< orphan*/  le_min_key_size_fops ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_sc_capable (struct hci_dev*) ; 
 struct l2cap_chan* smp_add_cid (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_del_chan (struct l2cap_chan*) ; 

int smp_register(struct hci_dev *hdev)
{
	struct l2cap_chan *chan;

	BT_DBG("%s", hdev->name);

	/* If the controller does not support Low Energy operation, then
	 * there is also no need to register any SMP channel.
	 */
	if (!lmp_le_capable(hdev))
		return 0;

	if (WARN_ON(hdev->smp_data)) {
		chan = hdev->smp_data;
		hdev->smp_data = NULL;
		smp_del_chan(chan);
	}

	chan = smp_add_cid(hdev, L2CAP_CID_SMP);
	if (IS_ERR(chan))
		return PTR_ERR(chan);

	hdev->smp_data = chan;

	debugfs_create_file("le_min_key_size", 0644, hdev->debugfs, hdev,
			    &le_min_key_size_fops);
	debugfs_create_file("le_max_key_size", 0644, hdev->debugfs, hdev,
			    &le_max_key_size_fops);

	/* If the controller does not support BR/EDR Secure Connections
	 * feature, then the BR/EDR SMP channel shall not be present.
	 *
	 * To test this with Bluetooth 4.0 controllers, create a debugfs
	 * switch that allows forcing BR/EDR SMP support and accepting
	 * cross-transport pairing on non-AES encrypted connections.
	 */
	if (!lmp_sc_capable(hdev)) {
		debugfs_create_file("force_bredr_smp", 0644, hdev->debugfs,
				    hdev, &force_bredr_smp_fops);

		/* Flag can be already set here (due to power toggle) */
		if (!hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
			return 0;
	}

	if (WARN_ON(hdev->smp_bredr_data)) {
		chan = hdev->smp_bredr_data;
		hdev->smp_bredr_data = NULL;
		smp_del_chan(chan);
	}

	chan = smp_add_cid(hdev, L2CAP_CID_SMP_BREDR);
	if (IS_ERR(chan)) {
		int err = PTR_ERR(chan);
		chan = hdev->smp_data;
		hdev->smp_data = NULL;
		smp_del_chan(chan);
		return err;
	}

	hdev->smp_bredr_data = chan;

	return 0;
}