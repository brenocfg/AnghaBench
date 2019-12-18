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
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_cp_read_local_oob_ext_data {int dummy; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_OOB_DATA ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_OOB_EXT_DATA ; 
 int /*<<< orphan*/  MGMT_OP_READ_LOCAL_OOB_EXT_DATA ; 
 scalar_t__ bredr_sc_enabled (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run_skb (struct hci_request*,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_cp_read_local_oob_ext_data*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  read_local_oob_ext_data_complete ; 

__attribute__((used)) static int read_local_ssp_oob_req(struct hci_dev *hdev, struct sock *sk,
				  struct mgmt_cp_read_local_oob_ext_data *cp)
{
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	int err;

	cmd = mgmt_pending_add(sk, MGMT_OP_READ_LOCAL_OOB_EXT_DATA, hdev,
			       cp, sizeof(*cp));
	if (!cmd)
		return -ENOMEM;

	hci_req_init(&req, hdev);

	if (bredr_sc_enabled(hdev))
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_EXT_DATA, 0, NULL);
	else
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_DATA, 0, NULL);

	err = hci_req_run_skb(&req, read_local_oob_ext_data_complete);
	if (err < 0) {
		mgmt_pending_remove(cmd);
		return err;
	}

	return 0;
}