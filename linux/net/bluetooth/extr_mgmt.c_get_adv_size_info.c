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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_rp_get_adv_size_info {int instance; void* max_scan_rsp_len; void* max_adv_data_len; int /*<<< orphan*/  flags; } ;
struct mgmt_cp_get_adv_size_info {int instance; int /*<<< orphan*/  flags; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int HCI_MAX_ADV_INSTANCES ; 
 int /*<<< orphan*/  MGMT_OP_GET_ADV_SIZE_INFO ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_supported_adv_flags (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_get_adv_size_info*,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tlv_data_max_len (struct hci_dev*,int,int) ; 

__attribute__((used)) static int get_adv_size_info(struct sock *sk, struct hci_dev *hdev,
			     void *data, u16 data_len)
{
	struct mgmt_cp_get_adv_size_info *cp = data;
	struct mgmt_rp_get_adv_size_info rp;
	u32 flags, supported_flags;
	int err;

	BT_DBG("%s", hdev->name);

	if (!lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_REJECTED);

	if (cp->instance < 1 || cp->instance > HCI_MAX_ADV_INSTANCES)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_INVALID_PARAMS);

	flags = __le32_to_cpu(cp->flags);

	/* The current implementation only supports a subset of the specified
	 * flags.
	 */
	supported_flags = get_supported_adv_flags(hdev);
	if (flags & ~supported_flags)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_INVALID_PARAMS);

	rp.instance = cp->instance;
	rp.flags = cp->flags;
	rp.max_adv_data_len = tlv_data_max_len(hdev, flags, true);
	rp.max_scan_rsp_len = tlv_data_max_len(hdev, flags, false);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				MGMT_STATUS_SUCCESS, &rp, sizeof(rp));

	return err;
}