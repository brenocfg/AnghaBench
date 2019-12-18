#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct ccid2_hc_tx_sock {long tx_srtt; long tx_mdev; long tx_mdev_max; long tx_rttvar; int tx_rto; int /*<<< orphan*/  tx_rtt_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_gss; int /*<<< orphan*/  dccps_gar; } ;

/* Variables and functions */
 int DCCP_RTO_MAX ; 
 scalar_t__ after48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 long max (long,int) ; 
 int tcp_rto_min (struct sock*) ; 

__attribute__((used)) static void ccid2_rtt_estimator(struct sock *sk, const long mrtt)
{
	struct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	long m = mrtt ? : 1;

	if (hc->tx_srtt == 0) {
		/* First measurement m */
		hc->tx_srtt = m << 3;
		hc->tx_mdev = m << 1;

		hc->tx_mdev_max = max(hc->tx_mdev, tcp_rto_min(sk));
		hc->tx_rttvar   = hc->tx_mdev_max;

		hc->tx_rtt_seq  = dccp_sk(sk)->dccps_gss;
	} else {
		/* Update scaled SRTT as SRTT += 1/8 * (m - SRTT) */
		m -= (hc->tx_srtt >> 3);
		hc->tx_srtt += m;

		/* Similarly, update scaled mdev with regard to |m| */
		if (m < 0) {
			m = -m;
			m -= (hc->tx_mdev >> 2);
			/*
			 * This neutralises RTO increase when RTT < SRTT - mdev
			 * (see P. Sarolahti, A. Kuznetsov,"Congestion Control
			 * in Linux TCP", USENIX 2002, pp. 49-62).
			 */
			if (m > 0)
				m >>= 3;
		} else {
			m -= (hc->tx_mdev >> 2);
		}
		hc->tx_mdev += m;

		if (hc->tx_mdev > hc->tx_mdev_max) {
			hc->tx_mdev_max = hc->tx_mdev;
			if (hc->tx_mdev_max > hc->tx_rttvar)
				hc->tx_rttvar = hc->tx_mdev_max;
		}

		/*
		 * Decay RTTVAR at most once per flight, exploiting that
		 *  1) pipe <= cwnd <= Sequence_Window = W  (RFC 4340, 7.5.2)
		 *  2) AWL = GSS-W+1 <= GAR <= GSS          (RFC 4340, 7.5.1)
		 * GAR is a useful bound for FlightSize = pipe.
		 * AWL is probably too low here, as it over-estimates pipe.
		 */
		if (after48(dccp_sk(sk)->dccps_gar, hc->tx_rtt_seq)) {
			if (hc->tx_mdev_max < hc->tx_rttvar)
				hc->tx_rttvar -= (hc->tx_rttvar -
						  hc->tx_mdev_max) >> 2;
			hc->tx_rtt_seq  = dccp_sk(sk)->dccps_gss;
			hc->tx_mdev_max = tcp_rto_min(sk);
		}
	}

	/*
	 * Set RTO from SRTT and RTTVAR
	 * As in TCP, 4 * RTTVAR >= TCP_RTO_MIN, giving a minimum RTO of 200 ms.
	 * This agrees with RFC 4341, 5:
	 *	"Because DCCP does not retransmit data, DCCP does not require
	 *	 TCP's recommended minimum timeout of one second".
	 */
	hc->tx_rto = (hc->tx_srtt >> 3) + hc->tx_rttvar;

	if (hc->tx_rto > DCCP_RTO_MAX)
		hc->tx_rto = DCCP_RTO_MAX;
}