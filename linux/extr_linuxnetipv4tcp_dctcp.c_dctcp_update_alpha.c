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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ snd_una; } ;
struct sock {int dummy; } ;
struct dctcp {scalar_t__ prior_snd_una; int acked_bytes_ecn; scalar_t__ dctcp_alpha; int /*<<< orphan*/  acked_bytes_total; int /*<<< orphan*/  next_seq; } ;
struct TYPE_3__ {scalar_t__ rcv_mss; } ;
struct TYPE_4__ {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 scalar_t__ CA_ACK_ECE ; 
 scalar_t__ CA_ACK_WIN_UPDATE ; 
 int /*<<< orphan*/  DCTCP_MAX_ALPHA ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dctcp_reset (struct tcp_sock const*,struct dctcp*) ; 
 scalar_t__ dctcp_shift_g ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct dctcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ min_not_zero (scalar_t__,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void dctcp_update_alpha(struct sock *sk, u32 flags)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct dctcp *ca = inet_csk_ca(sk);
	u32 acked_bytes = tp->snd_una - ca->prior_snd_una;

	/* If ack did not advance snd_una, count dupack as MSS size.
	 * If ack did update window, do not count it at all.
	 */
	if (acked_bytes == 0 && !(flags & CA_ACK_WIN_UPDATE))
		acked_bytes = inet_csk(sk)->icsk_ack.rcv_mss;
	if (acked_bytes) {
		ca->acked_bytes_total += acked_bytes;
		ca->prior_snd_una = tp->snd_una;

		if (flags & CA_ACK_ECE)
			ca->acked_bytes_ecn += acked_bytes;
	}

	/* Expired RTT */
	if (!before(tp->snd_una, ca->next_seq)) {
		u64 bytes_ecn = ca->acked_bytes_ecn;
		u32 alpha = ca->dctcp_alpha;

		/* alpha = (1 - g) * alpha + g * F */

		alpha -= min_not_zero(alpha, alpha >> dctcp_shift_g);
		if (bytes_ecn) {
			/* If dctcp_shift_g == 1, a 32bit value would overflow
			 * after 8 Mbytes.
			 */
			bytes_ecn <<= (10 - dctcp_shift_g);
			do_div(bytes_ecn, max(1U, ca->acked_bytes_total));

			alpha = min(alpha + (u32)bytes_ecn, DCTCP_MAX_ALPHA);
		}
		/* dctcp_alpha can be read from dctcp_get_info() without
		 * synchro, so we ask compiler to not use dctcp_alpha
		 * as a temporary variable in prior operations.
		 */
		WRITE_ONCE(ca->dctcp_alpha, alpha);
		dctcp_reset(tp, ca);
	}
}