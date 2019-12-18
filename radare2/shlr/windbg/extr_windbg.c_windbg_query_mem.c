#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int address_space; int flags; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_1__ r_query_mem; scalar_t__ ret; int /*<<< orphan*/  cpu; int /*<<< orphan*/  req; } ;
typedef  TYPE_2__ kd_req_t ;
typedef  int /*<<< orphan*/  kd_packet_t ;
struct TYPE_10__ {int seq_id; int /*<<< orphan*/  io_ptr; int /*<<< orphan*/  cpu; int /*<<< orphan*/  syncd; } ;
typedef  TYPE_3__ WindCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DbgKdQueryMemoryApi ; 
 int KD_E_OK ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_ACKNOWLEDGE ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_STATE_MANIPULATE ; 
 TYPE_2__* PKT_REQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kd_send_data_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int windbg_wait_packet (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int windbg_query_mem(WindCtx *ctx, const ut64 addr, int *address_space, int *flags) {
	kd_req_t req;
	kd_packet_t *pkt;
	int ret;

	if (!ctx || !ctx->io_ptr || !ctx->syncd) {
		return 0;
	}

	memset (&req, 0, sizeof(kd_req_t));

	req.req = DbgKdQueryMemoryApi;
	req.cpu = ctx->cpu;

	req.r_query_mem.addr = addr;
	req.r_query_mem.address_space = 0;	// Tells the kernel that 'addr' is a virtual address

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

	if (address_space) {
		*address_space = rr->r_query_mem.address_space;
	}
	if (flags) {
		*flags = rr->r_query_mem.flags;
	}

	free (pkt);

	return ret;

}