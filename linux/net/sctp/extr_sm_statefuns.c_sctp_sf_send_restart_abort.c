#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union sctp_addr_param {int dummy; } sctp_addr_param ;
struct TYPE_4__ {int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_1__ v4; } ;
struct sctp_packet {int dummy; } ;
struct sctp_errhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  cause; scalar_t__ variable; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_af {int (* to_addr_param ) (union sctp_addr*,union sctp_addr_param*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ctl_sock; } ;
struct net {TYPE_2__ sctp; } ;
struct TYPE_6__ {struct sctp_endpoint* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_DISCARD_PACKET ; 
 int /*<<< orphan*/  SCTP_CMD_SEND_PKT ; 
 int /*<<< orphan*/  SCTP_ERROR_RESTART ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_OUTCTRLCHUNKS ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_PACKET (struct sctp_packet*) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct sctp_packet* sctp_abort_pkt_new (struct net*,struct sctp_endpoint*,int /*<<< orphan*/ *,struct sctp_chunk*,struct sctp_errhdr*,int) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 TYPE_3__* sctp_sk (int /*<<< orphan*/ ) ; 
 int stub1 (union sctp_addr*,union sctp_addr_param*) ; 

__attribute__((used)) static int sctp_sf_send_restart_abort(struct net *net, union sctp_addr *ssa,
				      struct sctp_chunk *init,
				      struct sctp_cmd_seq *commands)
{
	struct sctp_af *af = sctp_get_af_specific(ssa->v4.sin_family);
	union sctp_addr_param *addrparm;
	struct sctp_errhdr *errhdr;
	char buffer[sizeof(*errhdr) + sizeof(*addrparm)];
	struct sctp_endpoint *ep;
	struct sctp_packet *pkt;
	int len;

	/* Build the error on the stack.   We are way to malloc crazy
	 * throughout the code today.
	 */
	errhdr = (struct sctp_errhdr *)buffer;
	addrparm = (union sctp_addr_param *)errhdr->variable;

	/* Copy into a parm format. */
	len = af->to_addr_param(ssa, addrparm);
	len += sizeof(*errhdr);

	errhdr->cause = SCTP_ERROR_RESTART;
	errhdr->length = htons(len);

	/* Assign to the control socket. */
	ep = sctp_sk(net->sctp.ctl_sock)->ep;

	/* Association is NULL since this may be a restart attack and we
	 * want to send back the attacker's vtag.
	 */
	pkt = sctp_abort_pkt_new(net, ep, NULL, init, errhdr, len);

	if (!pkt)
		goto out;
	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT, SCTP_PACKET(pkt));

	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	/* Discard the rest of the inbound packet. */
	sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_NULL());

out:
	/* Even if there is no memory, treat as a failure so
	 * the packet will get dropped.
	 */
	return 0;
}