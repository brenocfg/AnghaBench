#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_ulpevent {int dummy; } ;
struct sctp_errhdr {int cause; scalar_t__ variable; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunkhdr {int /*<<< orphan*/  type; } ;
struct sctp_chunk {scalar_t__ chunk_end; TYPE_1__* skb; } ;
struct TYPE_8__ {int /*<<< orphan*/  asconf_capable; } ;
struct TYPE_7__ {TYPE_2__* si; } ;
struct sctp_association {TYPE_4__ peer; int /*<<< orphan*/  ulpq; TYPE_3__ stream; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enqueue_event ) (int /*<<< orphan*/ *,struct sctp_ulpevent*) ;} ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  SCTP_CID_ASCONF 129 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
#define  SCTP_ERROR_UNKNOWN_CHUNK 128 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T4_RTO ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_remote_error (struct sctp_association*,struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_cmd_process_operr(struct sctp_cmd_seq *cmds,
				   struct sctp_association *asoc,
				   struct sctp_chunk *chunk)
{
	struct sctp_errhdr *err_hdr;
	struct sctp_ulpevent *ev;

	while (chunk->chunk_end > chunk->skb->data) {
		err_hdr = (struct sctp_errhdr *)(chunk->skb->data);

		ev = sctp_ulpevent_make_remote_error(asoc, chunk, 0,
						     GFP_ATOMIC);
		if (!ev)
			return;

		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);

		switch (err_hdr->cause) {
		case SCTP_ERROR_UNKNOWN_CHUNK:
		{
			struct sctp_chunkhdr *unk_chunk_hdr;

			unk_chunk_hdr = (struct sctp_chunkhdr *)
							err_hdr->variable;
			switch (unk_chunk_hdr->type) {
			/* ADDIP 4.1 A9) If the peer responds to an ASCONF with
			 * an ERROR chunk reporting that it did not recognized
			 * the ASCONF chunk type, the sender of the ASCONF MUST
			 * NOT send any further ASCONF chunks and MUST stop its
			 * T-4 timer.
			 */
			case SCTP_CID_ASCONF:
				if (asoc->peer.asconf_capable == 0)
					break;

				asoc->peer.asconf_capable = 0;
				sctp_add_cmd_sf(cmds, SCTP_CMD_TIMER_STOP,
					SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}