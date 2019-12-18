#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int reason; int tf; } ;
struct TYPE_7__ {TYPE_1__ r_cont; int /*<<< orphan*/  cpu; int /*<<< orphan*/  req; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ kd_req_t ;
struct TYPE_8__ {int seq_id; int /*<<< orphan*/ * plist_cache; int /*<<< orphan*/  io_ptr; int /*<<< orphan*/  cpu; int /*<<< orphan*/  syncd; } ;
typedef  TYPE_3__ WindCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DbgKdContinueApi2 ; 
 int KD_E_OK ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_ACKNOWLEDGE ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_STATE_MANIPULATE ; 
 int kd_send_data_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int windbg_wait_packet (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int windbg_continue(WindCtx *ctx) {
	kd_req_t req = {
		0
	};
	int ret;

	if (!ctx || !ctx->io_ptr || !ctx->syncd) {
		return 0;
	}
	req.req = DbgKdContinueApi2;
	req.cpu = ctx->cpu;
	req.r_cont.reason = 0x10001;
	// The meaning of 0x400 is unknown, but Windows doesn't
	// behave like suggested by ReactOS source
	req.r_cont.tf = 0x400;

	ret = kd_send_data_packet (ctx->io_ptr, KD_PACKET_TYPE_STATE_MANIPULATE,
		(ctx->seq_id ^= 1), (uint8_t *) &req, sizeof (kd_req_t), NULL, 0);
	if (ret == KD_E_OK) {
		ret = windbg_wait_packet (ctx, KD_PACKET_TYPE_ACKNOWLEDGE, NULL);
		if (ret == KD_E_OK) {
			// XXX What about DbgKdContinueApi ?
			r_list_free (ctx->plist_cache);
			ctx->plist_cache = NULL;
			return true;
		}
	}
	return false;
}