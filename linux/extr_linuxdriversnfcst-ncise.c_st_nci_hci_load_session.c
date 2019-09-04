#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct st_nci_pipe_info {scalar_t__ dst_gate_id; scalar_t__ src_host_id; int /*<<< orphan*/  pipe_state; } ;
struct sk_buff {int len; size_t* data; } ;
struct nci_dev {TYPE_4__* hci_dev; } ;
typedef  int /*<<< orphan*/  pipe_list ;
typedef  int /*<<< orphan*/  pipe_info ;
struct TYPE_11__ {size_t gate; } ;
struct TYPE_8__ {TYPE_1__* gates; } ;
struct TYPE_10__ {size_t* gate2pipe; TYPE_3__* pipes; TYPE_2__ init_data; } ;
struct TYPE_9__ {size_t gate; scalar_t__ host; } ;
struct TYPE_7__ {size_t pipe; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  NCI_HCI_LINK_MGMT_GATE ; 
 int /*<<< orphan*/  NCI_HCI_LINK_MGMT_PIPE ; 
 scalar_t__ ST_NCI_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST_NCI_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST_NCI_DEVICE_MGNT_PIPE ; 
 int /*<<< orphan*/  ST_NCI_DM_GETINFO ; 
 size_t ST_NCI_DM_GETINFO_PIPE_INFO ; 
 size_t ST_NCI_DM_GETINFO_PIPE_LIST ; 
 scalar_t__ ST_NCI_DM_IS_PIPE_OPEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_NCI_HOST_CONTROLLER_ID ; 
 size_t ST_NCI_TERMINAL_HOST_ID ; 
 scalar_t__ ST_NCI_UICC_HOST_ID ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nci_hci_connect_gate (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nci_hci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 TYPE_5__* st_nci_gates ; 

int st_nci_hci_load_session(struct nci_dev *ndev)
{
	int i, j, r;
	struct sk_buff *skb_pipe_list, *skb_pipe_info;
	struct st_nci_pipe_info *dm_pipe_info;
	u8 pipe_list[] = { ST_NCI_DM_GETINFO_PIPE_LIST,
			ST_NCI_TERMINAL_HOST_ID};
	u8 pipe_info[] = { ST_NCI_DM_GETINFO_PIPE_INFO,
			ST_NCI_TERMINAL_HOST_ID, 0};

	/* On ST_NCI device pipes number are dynamics
	 * If pipes are already created, hci_dev_up will fail.
	 * Doing a clear all pipe is a bad idea because:
	 * - It does useless EEPROM cycling
	 * - It might cause issue for secure elements support
	 * (such as removing connectivity or APDU reader pipe)
	 * A better approach on ST_NCI is to:
	 * - get a pipe list for each host.
	 * (eg: ST_NCI_HOST_CONTROLLER_ID for now).
	 * (TODO Later on UICC HOST and eSE HOST)
	 * - get pipe information
	 * - match retrieved pipe list in st_nci_gates
	 * ST_NCI_DEVICE_MGNT_GATE is a proprietary gate
	 * with ST_NCI_DEVICE_MGNT_PIPE.
	 * Pipe can be closed and need to be open.
	 */
	r = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTROLLER_ID,
				ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_DEVICE_MGNT_PIPE);
	if (r < 0)
		return r;

	/* Get pipe list */
	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_DM_GETINFO, pipe_list, sizeof(pipe_list),
			&skb_pipe_list);
	if (r < 0)
		return r;

	/* Complete the existing gate_pipe table */
	for (i = 0; i < skb_pipe_list->len; i++) {
		pipe_info[2] = skb_pipe_list->data[i];
		r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
					ST_NCI_DM_GETINFO, pipe_info,
					sizeof(pipe_info), &skb_pipe_info);

		if (r)
			continue;

		/*
		 * Match pipe ID and gate ID
		 * Output format from ST21NFC_DM_GETINFO is:
		 * - pipe state (1byte)
		 * - source hid (1byte)
		 * - source gid (1byte)
		 * - destination hid (1byte)
		 * - destination gid (1byte)
		 */
		dm_pipe_info = (struct st_nci_pipe_info *)skb_pipe_info->data;
		if (dm_pipe_info->dst_gate_id == ST_NCI_APDU_READER_GATE &&
		    dm_pipe_info->src_host_id == ST_NCI_UICC_HOST_ID) {
			pr_err("Unexpected apdu_reader pipe on host %x\n",
			       dm_pipe_info->src_host_id);
			kfree_skb(skb_pipe_info);
			continue;
		}

		for (j = 3; (j < ARRAY_SIZE(st_nci_gates)) &&
		     (st_nci_gates[j].gate != dm_pipe_info->dst_gate_id); j++)
			;

		if (j < ARRAY_SIZE(st_nci_gates) &&
		    st_nci_gates[j].gate == dm_pipe_info->dst_gate_id &&
		    ST_NCI_DM_IS_PIPE_OPEN(dm_pipe_info->pipe_state)) {
			ndev->hci_dev->init_data.gates[j].pipe = pipe_info[2];

			ndev->hci_dev->gate2pipe[st_nci_gates[j].gate] =
						pipe_info[2];
			ndev->hci_dev->pipes[pipe_info[2]].gate =
						st_nci_gates[j].gate;
			ndev->hci_dev->pipes[pipe_info[2]].host =
						dm_pipe_info->src_host_id;
		}
		kfree_skb(skb_pipe_info);
	}

	/*
	 * 3 gates have a well known pipe ID. Only NCI_HCI_LINK_MGMT_GATE
	 * is not yet open at this stage.
	 */
	r = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTROLLER_ID,
				 NCI_HCI_LINK_MGMT_GATE,
				 NCI_HCI_LINK_MGMT_PIPE);

	kfree_skb(skb_pipe_list);
	return r;
}