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
typedef  int u32 ;
struct sock {int dummy; } ;
struct ccid2_hc_tx_sock {int tx_cwnd; int tx_cwnd_stamp; void* tx_cwnd_used; void* tx_ssthresh; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_mss_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccid2_check_l_ack_ratio (struct sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 void* max (void*,int) ; 
 int rfc3390_bytes_to_packets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid2_cwnd_application_limited(struct sock *sk, const u32 now)
{
	struct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	/* don't reduce cwnd below the initial window (IW) */
	u32 init_win = rfc3390_bytes_to_packets(dccp_sk(sk)->dccps_mss_cache),
	    win_used = max(hc->tx_cwnd_used, init_win);

	if (win_used < hc->tx_cwnd) {
		hc->tx_ssthresh = max(hc->tx_ssthresh,
				     (hc->tx_cwnd >> 1) + (hc->tx_cwnd >> 2));
		hc->tx_cwnd = (hc->tx_cwnd + win_used) >> 1;
	}
	hc->tx_cwnd_used  = 0;
	hc->tx_cwnd_stamp = now;

	ccid2_check_l_ack_ratio(sk);
}