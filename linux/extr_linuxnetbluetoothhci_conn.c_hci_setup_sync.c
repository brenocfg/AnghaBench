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
struct sco_param {int /*<<< orphan*/  max_latency; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  retrans_effort; } ;
struct hci_dev {int dummy; } ;
struct hci_cp_setup_sync_conn {void* max_latency; void* pkt_type; int /*<<< orphan*/  retrans_effort; void* voice_setting; void* rx_bandwidth; void* tx_bandwidth; void* handle; } ;
struct hci_conn {int out; size_t attempt; int setting; int /*<<< orphan*/  link; int /*<<< orphan*/  state; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int __u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct sco_param*) ; 
 int /*<<< orphan*/  BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  HCI_OP_SETUP_SYNC_CONN ; 
#define  SCO_AIRMODE_CVSD 129 
 int SCO_AIRMODE_MASK ; 
#define  SCO_AIRMODE_TRANSP 128 
 void* __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 struct sco_param* esco_param_cvsd ; 
 struct sco_param* esco_param_msbc ; 
 scalar_t__ hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_setup_sync_conn*) ; 
 int /*<<< orphan*/  lmp_esco_capable (int /*<<< orphan*/ ) ; 
 struct sco_param* sco_param_cvsd ; 

bool hci_setup_sync(struct hci_conn *conn, __u16 handle)
{
	struct hci_dev *hdev = conn->hdev;
	struct hci_cp_setup_sync_conn cp;
	const struct sco_param *param;

	BT_DBG("hcon %p", conn);

	conn->state = BT_CONNECT;
	conn->out = true;

	conn->attempt++;

	cp.handle   = cpu_to_le16(handle);

	cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
	cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
	cp.voice_setting  = cpu_to_le16(conn->setting);

	switch (conn->setting & SCO_AIRMODE_MASK) {
	case SCO_AIRMODE_TRANSP:
		if (conn->attempt > ARRAY_SIZE(esco_param_msbc))
			return false;
		param = &esco_param_msbc[conn->attempt - 1];
		break;
	case SCO_AIRMODE_CVSD:
		if (lmp_esco_capable(conn->link)) {
			if (conn->attempt > ARRAY_SIZE(esco_param_cvsd))
				return false;
			param = &esco_param_cvsd[conn->attempt - 1];
		} else {
			if (conn->attempt > ARRAY_SIZE(sco_param_cvsd))
				return false;
			param = &sco_param_cvsd[conn->attempt - 1];
		}
		break;
	default:
		return false;
	}

	cp.retrans_effort = param->retrans_effort;
	cp.pkt_type = __cpu_to_le16(param->pkt_type);
	cp.max_latency = __cpu_to_le16(param->max_latency);

	if (hci_send_cmd(hdev, HCI_OP_SETUP_SYNC_CONN, sizeof(cp), &cp) < 0)
		return false;

	return true;
}