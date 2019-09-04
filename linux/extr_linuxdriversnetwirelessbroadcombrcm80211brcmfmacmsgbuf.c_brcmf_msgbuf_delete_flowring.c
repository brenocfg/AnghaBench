#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {scalar_t__ request_id; int /*<<< orphan*/  ifidx; int /*<<< orphan*/  msgtype; } ;
struct msgbuf_tx_flowring_delete_req {scalar_t__ reason; int /*<<< orphan*/  flow_ring_id; TYPE_2__ msg; } ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  flow; struct brcmf_commonring** commonrings; } ;
struct brcmf_commonring {int dummy; } ;
struct TYPE_3__ {scalar_t__ pd; } ;

/* Variables and functions */
 size_t BRCMF_H2D_MSGRING_CONTROL_SUBMIT ; 
 scalar_t__ BRCMF_H2D_MSGRING_FLOWRING_IDSTART ; 
 int /*<<< orphan*/  MSGBUF ; 
 int /*<<< orphan*/  MSGBUF_TYPE_FLOW_RING_DELETE ; 
 int /*<<< orphan*/  brcmf_commonring_lock (struct brcmf_commonring*) ; 
 void* brcmf_commonring_reserve_for_write (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_unlock (struct brcmf_commonring*) ; 
 int brcmf_commonring_write_complete (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_flowring_ifidx_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_msgbuf_remove_flowring (struct brcmf_msgbuf*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 

void brcmf_msgbuf_delete_flowring(struct brcmf_pub *drvr, u16 flowid)
{
	struct brcmf_msgbuf *msgbuf = (struct brcmf_msgbuf *)drvr->proto->pd;
	struct msgbuf_tx_flowring_delete_req *delete;
	struct brcmf_commonring *commonring;
	void *ret_ptr;
	u8 ifidx;
	int err;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_for_write(commonring);
	if (!ret_ptr) {
		brcmf_err("FW unaware, flowring will be removed !!\n");
		brcmf_commonring_unlock(commonring);
		brcmf_msgbuf_remove_flowring(msgbuf, flowid);
		return;
	}

	delete = (struct msgbuf_tx_flowring_delete_req *)ret_ptr;

	ifidx = brcmf_flowring_ifidx_get(msgbuf->flow, flowid);

	delete->msg.msgtype = MSGBUF_TYPE_FLOW_RING_DELETE;
	delete->msg.ifidx = ifidx;
	delete->msg.request_id = 0;

	delete->flow_ring_id = cpu_to_le16(flowid +
					   BRCMF_H2D_MSGRING_FLOWRING_IDSTART);
	delete->reason = 0;

	brcmf_dbg(MSGBUF, "Send Flow Delete Req flow ID %d, ifindex %d\n",
		  flowid, ifidx);

	err = brcmf_commonring_write_complete(commonring);
	brcmf_commonring_unlock(commonring);
	if (err) {
		brcmf_err("Failed to submit RING_DELETE, flowring will be removed\n");
		brcmf_msgbuf_remove_flowring(msgbuf, flowid);
	}
}