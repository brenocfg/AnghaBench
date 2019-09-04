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
struct sock {int dummy; } ;
struct sctp_transport {int param_flags; scalar_t__ pathmtu; TYPE_2__* dst; struct sctp_association* asoc; int /*<<< orphan*/  fl; int /*<<< orphan*/  saddr; TYPE_1__* af_specific; } ;
struct sctp_association {scalar_t__ pathmtu; } ;
struct TYPE_4__ {scalar_t__ obsolete; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_dst ) (struct sctp_transport*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ SCTP_DEFAULT_MAXSEGMENT ; 
 int SPP_PMTUD_DISABLE ; 
 scalar_t__ sctp_dst_mtu (TYPE_2__*) ; 
 int /*<<< orphan*/  sctp_transport_dst_release (struct sctp_transport*) ; 
 int /*<<< orphan*/  stub1 (struct sctp_transport*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock*) ; 

void sctp_transport_pmtu(struct sctp_transport *transport, struct sock *sk)
{
	/* If we don't have a fresh route, look one up */
	if (!transport->dst || transport->dst->obsolete) {
		sctp_transport_dst_release(transport);
		transport->af_specific->get_dst(transport, &transport->saddr,
						&transport->fl, sk);
	}

	if (transport->param_flags & SPP_PMTUD_DISABLE) {
		struct sctp_association *asoc = transport->asoc;

		if (!transport->pathmtu && asoc && asoc->pathmtu)
			transport->pathmtu = asoc->pathmtu;
		if (transport->pathmtu)
			return;
	}

	if (transport->dst)
		transport->pathmtu = sctp_dst_mtu(transport->dst);
	else
		transport->pathmtu = SCTP_DEFAULT_MAXSEGMENT;
}