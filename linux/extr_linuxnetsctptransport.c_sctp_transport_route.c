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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_transport {int /*<<< orphan*/  saddr; scalar_t__ dst; int /*<<< orphan*/  fl; struct sctp_af* af_specific; struct sctp_association* asoc; } ;
struct sctp_sock {TYPE_2__* pf; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {struct sctp_transport* active_path; int /*<<< orphan*/  primary_path; } ;
struct sctp_association {TYPE_3__ base; TYPE_1__ peer; } ;
struct sctp_af {int /*<<< orphan*/  (* get_saddr ) (struct sctp_sock*,struct sctp_transport*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_dst ) (struct sctp_transport*,union sctp_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* to_sk_saddr ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union sctp_addr*,int) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 int /*<<< orphan*/  sctp_transport_dst_release (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_pmtu (struct sctp_transport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sctp_transport*,union sctp_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sctp_sock*,struct sctp_transport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sctp_transport_route(struct sctp_transport *transport,
			  union sctp_addr *saddr, struct sctp_sock *opt)
{
	struct sctp_association *asoc = transport->asoc;
	struct sctp_af *af = transport->af_specific;

	sctp_transport_dst_release(transport);
	af->get_dst(transport, saddr, &transport->fl, sctp_opt2sk(opt));

	if (saddr)
		memcpy(&transport->saddr, saddr, sizeof(union sctp_addr));
	else
		af->get_saddr(opt, transport, &transport->fl);

	sctp_transport_pmtu(transport, sctp_opt2sk(opt));

	/* Initialize sk->sk_rcv_saddr, if the transport is the
	 * association's active path for getsockname().
	 */
	if (transport->dst && asoc &&
	    (!asoc->peer.primary_path || transport == asoc->peer.active_path))
		opt->pf->to_sk_saddr(&transport->saddr, asoc->base.sk);
}