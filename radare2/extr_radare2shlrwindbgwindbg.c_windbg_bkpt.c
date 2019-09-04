#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int handle; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int handle; } ;
struct TYPE_10__ {int ret; TYPE_2__ r_set_bp; TYPE_1__ r_del_bp; int /*<<< orphan*/  cpu; int /*<<< orphan*/  req; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ kd_req_t ;
typedef  int /*<<< orphan*/  kd_packet_t ;
struct TYPE_11__ {int seq_id; int /*<<< orphan*/  io_ptr; int /*<<< orphan*/  cpu; int /*<<< orphan*/  syncd; } ;
typedef  TYPE_4__ WindCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DbgKdRestoreBreakPointApi ; 
 int /*<<< orphan*/  DbgKdWriteBreakPointApi ; 
 int KD_E_OK ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_ACKNOWLEDGE ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_STATE_MANIPULATE ; 
 TYPE_3__* PKT_REQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kd_send_data_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int windbg_wait_packet (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int windbg_bkpt(WindCtx *ctx, const ut64 addr, const int set, const int hw, int *handle) {
	kd_req_t req = {
		0
	};
	kd_packet_t *pkt;
	int ret;

	if (!ctx || !ctx->io_ptr || !ctx->syncd) {
		return 0;
	}

	req.req = set? DbgKdWriteBreakPointApi: DbgKdRestoreBreakPointApi;
	req.cpu = ctx->cpu;

	if (set) {
		req.r_set_bp.addr = addr;
	} else {
		req.r_del_bp.handle = *handle;
	}

	ret = kd_send_data_packet (ctx->io_ptr, KD_PACKET_TYPE_STATE_MANIPULATE, (ctx->seq_id ^= 1), (uint8_t *) &req,
		sizeof(kd_req_t), NULL, 0);
	if (ret != KD_E_OK) {
		return 0;
	}

	ret = windbg_wait_packet (ctx, KD_PACKET_TYPE_ACKNOWLEDGE, NULL);
	if (ret != KD_E_OK) {
		return 0;
	}

	ret = windbg_wait_packet (ctx, KD_PACKET_TYPE_STATE_MANIPULATE, &pkt);
	if (ret != KD_E_OK) {
		return 0;
	}

	kd_req_t *rr = PKT_REQ (pkt);

	if (rr->ret) {
		free (pkt);
		return 0;
	}
	*handle = rr->r_set_bp.handle;
	ret = !!rr->ret;
	free (pkt);
	return ret;
}