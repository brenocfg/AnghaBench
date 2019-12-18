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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
struct sctp_paramhdr {int dummy; } ;
struct sctp_errhdr {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_8__ {scalar_t__ addip_hdr; } ;
struct sctp_chunk {TYPE_4__ subh; TYPE_3__* skb; int /*<<< orphan*/  auth; } ;
struct TYPE_5__ {int /*<<< orphan*/  asconf_capable; } ;
struct sctp_association {scalar_t__ addip_serial; struct sctp_chunk* addip_last_asconf; TYPE_1__ peer; } ;
struct sctp_addiphdr {int /*<<< orphan*/  serial; } ;
struct sctp_addip_chunk {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  addip_noauth; } ;
struct net {TYPE_2__ sctp; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;
typedef  scalar_t__ __u32 ;
struct TYPE_7__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ADDIP_SERIAL_gte (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_DISCARD_PACKET ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_REPORT_BAD_TAG ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_DEC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int SCTP_DISPOSITION_ABORT ; 
 int SCTP_DISPOSITION_DISCARD ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_ASCONF_ACK ; 
 int /*<<< orphan*/  SCTP_ERROR_RSRC_LOW ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T4_RTO ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_ABORTEDS ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,struct sctp_chunk*,int) ; 
 int /*<<< orphan*/  sctp_process_asconf_ack (struct sctp_association*,struct sctp_chunk*) ; 
 int sctp_send_next_asconf (struct net*,struct sctp_endpoint const*,struct sctp_association*,union sctp_subtype const,struct sctp_cmd_seq*) ; 
 int sctp_sf_discard_chunk (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_pdiscard (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_paramlen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,void*,struct sctp_cmd_seq*) ; 
 int /*<<< orphan*/  sctp_verify_asconf (struct sctp_association const*,struct sctp_chunk*,int,struct sctp_paramhdr**) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 

enum sctp_disposition sctp_sf_do_asconf_ack(struct net *net,
					    const struct sctp_endpoint *ep,
					    const struct sctp_association *asoc,
					    const union sctp_subtype type,
					    void *arg,
					    struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *last_asconf = asoc->addip_last_asconf;
	struct sctp_paramhdr *err_param = NULL;
	struct sctp_chunk *asconf_ack = arg;
	struct sctp_addiphdr *addip_hdr;
	__u32 sent_serial, rcvd_serial;
	struct sctp_chunk *abort;

	if (!sctp_vtag_verify(asconf_ack, asoc)) {
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_NULL());
		return sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	}

	/* ADD-IP, Section 4.1.2:
	 * This chunk MUST be sent in an authenticated way by using
	 * the mechanism defined in [I-D.ietf-tsvwg-sctp-auth]. If this chunk
	 * is received unauthenticated it MUST be silently discarded as
	 * described in [I-D.ietf-tsvwg-sctp-auth].
	 */
	if (!asoc->peer.asconf_capable ||
	    (!net->sctp.addip_noauth && !asconf_ack->auth))
		return sctp_sf_discard_chunk(net, ep, asoc, type, arg,
					     commands);

	/* Make sure that the ADDIP chunk has a valid length.  */
	if (!sctp_chunk_length_valid(asconf_ack,
				     sizeof(struct sctp_addip_chunk)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	addip_hdr = (struct sctp_addiphdr *)asconf_ack->skb->data;
	rcvd_serial = ntohl(addip_hdr->serial);

	/* Verify the ASCONF-ACK chunk before processing it. */
	if (!sctp_verify_asconf(asoc, asconf_ack, false, &err_param))
		return sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
			   (void *)err_param, commands);

	if (last_asconf) {
		addip_hdr = (struct sctp_addiphdr *)last_asconf->subh.addip_hdr;
		sent_serial = ntohl(addip_hdr->serial);
	} else {
		sent_serial = asoc->addip_serial - 1;
	}

	/* D0) If an endpoint receives an ASCONF-ACK that is greater than or
	 * equal to the next serial number to be used but no ASCONF chunk is
	 * outstanding the endpoint MUST ABORT the association. Note that a
	 * sequence number is greater than if it is no more than 2^^31-1
	 * larger than the current sequence number (using serial arithmetic).
	 */
	if (ADDIP_SERIAL_gte(rcvd_serial, sent_serial + 1) &&
	    !(asoc->addip_last_asconf)) {
		abort = sctp_make_abort(asoc, asconf_ack,
					sizeof(struct sctp_errhdr));
		if (abort) {
			sctp_init_cause(abort, SCTP_ERROR_ASCONF_ACK, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(abort));
		}
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_NULL());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		return SCTP_DISPOSITION_ABORT;
	}

	if ((rcvd_serial == sent_serial) && asoc->addip_last_asconf) {
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));

		if (!sctp_process_asconf_ack((struct sctp_association *)asoc,
					     asconf_ack))
			return sctp_send_next_asconf(net, ep,
					(struct sctp_association *)asoc,
							type, commands);

		abort = sctp_make_abort(asoc, asconf_ack,
					sizeof(struct sctp_errhdr));
		if (abort) {
			sctp_init_cause(abort, SCTP_ERROR_RSRC_LOW, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(abort));
		}
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_NULL());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		return SCTP_DISPOSITION_ABORT;
	}

	return SCTP_DISPOSITION_DISCARD;
}