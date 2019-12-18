#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct sock {int dummy; } ;
struct ccid3_hc_rx_sock {scalar_t__ rx_rtt; unsigned int rx_bytes_recv; scalar_t__ rx_x_recv; int rx_s; int /*<<< orphan*/  rx_tstamp_last_feedback; } ;
typedef  unsigned int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG (char*) ; 
 scalar_t__ DCCP_FALLBACK_RTT ; 
 int /*<<< orphan*/  DCCP_WARN (char*) ; 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int /*<<< orphan*/ ,struct sock*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 unsigned int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int scaled_div (int,unsigned int) ; 
 void* scaled_div32 (unsigned int,unsigned int) ; 
 unsigned int tfrc_calc_x_reverse_lookup (unsigned int) ; 

__attribute__((used)) static u32 ccid3_first_li(struct sock *sk)
{
	struct ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	u32 x_recv, p;
	s64 delta;
	u64 fval;

	if (hc->rx_rtt == 0) {
		DCCP_WARN("No RTT estimate available, using fallback RTT\n");
		hc->rx_rtt = DCCP_FALLBACK_RTT;
	}

	delta = ktime_us_delta(ktime_get(), hc->rx_tstamp_last_feedback);
	if (delta <= 0)
		delta = 1;
	x_recv = scaled_div32(hc->rx_bytes_recv, delta);
	if (x_recv == 0) {		/* would also trigger divide-by-zero */
		DCCP_WARN("X_recv==0\n");
		if (hc->rx_x_recv == 0) {
			DCCP_BUG("stored value of X_recv is zero");
			return ~0U;
		}
		x_recv = hc->rx_x_recv;
	}

	fval = scaled_div(hc->rx_s, hc->rx_rtt);
	fval = scaled_div32(fval, x_recv);
	p = tfrc_calc_x_reverse_lookup(fval);

	ccid3_pr_debug("%s(%p), receive rate=%u bytes/s, implied "
		       "loss rate=%u\n", dccp_role(sk), sk, x_recv, p);

	return p == 0 ? ~0U : scaled_div(1, p);
}