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
struct sock {int dummy; } ;
struct mgmt_addr_info {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_add_remote_oob_ext_data {struct mgmt_addr_info addr; int /*<<< orphan*/ * hash256; int /*<<< orphan*/ * rand256; int /*<<< orphan*/ * hash192; int /*<<< orphan*/ * rand192; } ;
struct mgmt_cp_add_remote_oob_data {struct mgmt_addr_info addr; int /*<<< orphan*/ * rand; int /*<<< orphan*/ * hash; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BDADDR_BREDR ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_ADD_REMOTE_OOB_DATA_SIZE ; 
 int /*<<< orphan*/  MGMT_ADD_REMOTE_OOB_EXT_DATA_SIZE ; 
 int /*<<< orphan*/  MGMT_OP_ADD_REMOTE_OOB_DATA ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ZERO_KEY ; 
 scalar_t__ bdaddr_type_is_le (scalar_t__) ; 
 int /*<<< orphan*/  bdaddr_type_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 int hci_add_remote_oob_data (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_addr_info*,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_remote_oob_data(struct sock *sk, struct hci_dev *hdev,
			       void *data, u16 len)
{
	struct mgmt_addr_info *addr = data;
	int err;

	BT_DBG("%s ", hdev->name);

	if (!bdaddr_type_is_valid(addr->type))
		return mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_ADD_REMOTE_OOB_DATA,
					 MGMT_STATUS_INVALID_PARAMS,
					 addr, sizeof(*addr));

	hci_dev_lock(hdev);

	if (len == MGMT_ADD_REMOTE_OOB_DATA_SIZE) {
		struct mgmt_cp_add_remote_oob_data *cp = data;
		u8 status;

		if (cp->addr.type != BDADDR_BREDR) {
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_ADD_REMOTE_OOB_DATA,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, sizeof(cp->addr));
			goto unlock;
		}

		err = hci_add_remote_oob_data(hdev, &cp->addr.bdaddr,
					      cp->addr.type, cp->hash,
					      cp->rand, NULL, NULL);
		if (err < 0)
			status = MGMT_STATUS_FAILED;
		else
			status = MGMT_STATUS_SUCCESS;

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_ADD_REMOTE_OOB_DATA, status,
					&cp->addr, sizeof(cp->addr));
	} else if (len == MGMT_ADD_REMOTE_OOB_EXT_DATA_SIZE) {
		struct mgmt_cp_add_remote_oob_ext_data *cp = data;
		u8 *rand192, *hash192, *rand256, *hash256;
		u8 status;

		if (bdaddr_type_is_le(cp->addr.type)) {
			/* Enforce zero-valued 192-bit parameters as
			 * long as legacy SMP OOB isn't implemented.
			 */
			if (memcmp(cp->rand192, ZERO_KEY, 16) ||
			    memcmp(cp->hash192, ZERO_KEY, 16)) {
				err = mgmt_cmd_complete(sk, hdev->id,
							MGMT_OP_ADD_REMOTE_OOB_DATA,
							MGMT_STATUS_INVALID_PARAMS,
							addr, sizeof(*addr));
				goto unlock;
			}

			rand192 = NULL;
			hash192 = NULL;
		} else {
			/* In case one of the P-192 values is set to zero,
			 * then just disable OOB data for P-192.
			 */
			if (!memcmp(cp->rand192, ZERO_KEY, 16) ||
			    !memcmp(cp->hash192, ZERO_KEY, 16)) {
				rand192 = NULL;
				hash192 = NULL;
			} else {
				rand192 = cp->rand192;
				hash192 = cp->hash192;
			}
		}

		/* In case one of the P-256 values is set to zero, then just
		 * disable OOB data for P-256.
		 */
		if (!memcmp(cp->rand256, ZERO_KEY, 16) ||
		    !memcmp(cp->hash256, ZERO_KEY, 16)) {
			rand256 = NULL;
			hash256 = NULL;
		} else {
			rand256 = cp->rand256;
			hash256 = cp->hash256;
		}

		err = hci_add_remote_oob_data(hdev, &cp->addr.bdaddr,
					      cp->addr.type, hash192, rand192,
					      hash256, rand256);
		if (err < 0)
			status = MGMT_STATUS_FAILED;
		else
			status = MGMT_STATUS_SUCCESS;

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_ADD_REMOTE_OOB_DATA,
					status, &cp->addr, sizeof(cp->addr));
	} else {
		bt_dev_err(hdev, "add_remote_oob_data: invalid len of %u bytes",
			   len);
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_REMOTE_OOB_DATA,
				      MGMT_STATUS_INVALID_PARAMS);
	}

unlock:
	hci_dev_unlock(hdev);
	return err;
}