#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ const type; scalar_t__ leader; } ;
typedef  TYPE_1__ kd_packet_t ;
struct TYPE_11__ {int /*<<< orphan*/  io_ptr; } ;
typedef  TYPE_2__ WindCtx ;

/* Variables and functions */
 int KD_E_MALFORMED ; 
 int KD_E_OK ; 
 scalar_t__ KD_PACKET_CTRL ; 
 scalar_t__ KD_PACKET_DATA ; 
 scalar_t__ KD_PACKET_TYPE_FILE_IO ; 
 scalar_t__ KD_PACKET_TYPE_RESEND ; 
 scalar_t__ KD_PACKET_TYPE_STATE_CHANGE64 ; 
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  do_io_reply (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int kd_read_packet (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  r_sys_backtrace () ; 

int windbg_wait_packet(WindCtx *ctx, const uint32_t type, kd_packet_t **p) {
	kd_packet_t *pkt = NULL;
	int ret;
	int retries = 10;

	do {
		if (pkt) {
			R_FREE (pkt);
		}
		// Try to read a whole packet
		ret = kd_read_packet (ctx->io_ptr, &pkt);
		if (ret != KD_E_OK || !pkt) {
			break;
		}

		// eprintf ("Received %08x\n", pkt->type);
		if (pkt->type != type) {
			eprintf ("We were not waiting for this... %08x\n", pkt->type);
		}
		if (pkt->leader == KD_PACKET_DATA && pkt->type == KD_PACKET_TYPE_STATE_CHANGE64) {
			// dump_stc (pkt);
			eprintf ("State64\n");
		}
		if (pkt->leader == KD_PACKET_DATA && pkt->type == KD_PACKET_TYPE_FILE_IO) {
			eprintf ("Replying IO\n");
			do_io_reply (ctx, pkt);
		}

		// Check for RESEND
		// The host didn't like our request
		if (pkt->leader == KD_PACKET_CTRL && pkt->type == KD_PACKET_TYPE_RESEND) {
			r_sys_backtrace ();
			eprintf ("Waoh. You probably sent a malformed packet !\n");
			ret = KD_E_MALFORMED;
			//break;
		}
	} while (pkt->type != type && retries--);

	if (ret != KD_E_OK) {
		free (pkt);
		return ret;
	}

	if (p) {
		*p = pkt;
	} else {
		free (pkt);
	}

	return KD_E_OK;
}