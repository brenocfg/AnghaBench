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
struct TYPE_6__ {scalar_t__ cacc_saw_newack; scalar_t__ next_tsn_at_change; scalar_t__ cycling_changeover; scalar_t__ changeover_active; } ;
struct sctp_transport {TYPE_3__ cacc; scalar_t__ hb_sent; scalar_t__ rto_pending; scalar_t__ error_count; scalar_t__ flight_size; scalar_t__ partial_bytes_acked; scalar_t__ rttvar; scalar_t__ srtt; scalar_t__ rtt; int /*<<< orphan*/  rto; int /*<<< orphan*/  ssthresh; scalar_t__ burst_limited; int /*<<< orphan*/  cwnd; struct sctp_association* asoc; } ;
struct TYPE_4__ {int /*<<< orphan*/  a_rwnd; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
struct sctp_association {int pathmtu; int /*<<< orphan*/  rto_initial; TYPE_2__ peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __u32 ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_max_rto (struct sctp_association*,struct sctp_transport*) ; 

void sctp_transport_reset(struct sctp_transport *t)
{
	struct sctp_association *asoc = t->asoc;

	/* RFC 2960 (bis), Section 5.2.4
	 * All the congestion control parameters (e.g., cwnd, ssthresh)
	 * related to this peer MUST be reset to their initial values
	 * (see Section 6.2.1)
	 */
	t->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));
	t->burst_limited = 0;
	t->ssthresh = asoc->peer.i.a_rwnd;
	t->rto = asoc->rto_initial;
	sctp_max_rto(asoc, t);
	t->rtt = 0;
	t->srtt = 0;
	t->rttvar = 0;

	/* Reset these additional variables so that we have a clean slate. */
	t->partial_bytes_acked = 0;
	t->flight_size = 0;
	t->error_count = 0;
	t->rto_pending = 0;
	t->hb_sent = 0;

	/* Initialize the state information for SFR-CACC */
	t->cacc.changeover_active = 0;
	t->cacc.cycling_changeover = 0;
	t->cacc.next_tsn_at_change = 0;
	t->cacc.cacc_saw_newack = 0;
}