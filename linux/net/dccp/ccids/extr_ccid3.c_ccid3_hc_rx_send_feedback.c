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
struct sk_buff {int dummy; } ;
struct dccp_sock {int dccps_hc_rx_insert_options; } ;
struct ccid3_hc_rx_sock {unsigned int rx_pinv; scalar_t__ rx_bytes_recv; int /*<<< orphan*/  rx_last_counter; int /*<<< orphan*/  rx_tstamp_last_feedback; int /*<<< orphan*/  rx_x_recv; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum ccid3_fback_type { ____Placeholder_ccid3_fback_type } ccid3_fback_type ;
struct TYPE_2__ {int /*<<< orphan*/  dccph_ccval; } ;

/* Variables and functions */
#define  CCID3_FBACK_INITIAL 130 
#define  CCID3_FBACK_PARAM_CHANGE 129 
#define  CCID3_FBACK_PERIODIC 128 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* dccp_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaled_div32 (scalar_t__,int) ; 

__attribute__((used)) static void ccid3_hc_rx_send_feedback(struct sock *sk,
				      const struct sk_buff *skb,
				      enum ccid3_fback_type fbtype)
{
	struct ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	struct dccp_sock *dp = dccp_sk(sk);
	ktime_t now = ktime_get();
	s64 delta = 0;

	switch (fbtype) {
	case CCID3_FBACK_INITIAL:
		hc->rx_x_recv = 0;
		hc->rx_pinv   = ~0U;   /* see RFC 4342, 8.5 */
		break;
	case CCID3_FBACK_PARAM_CHANGE:
		/*
		 * When parameters change (new loss or p > p_prev), we do not
		 * have a reliable estimate for R_m of [RFC 3448, 6.2] and so
		 * need to  reuse the previous value of X_recv. However, when
		 * X_recv was 0 (due to early loss), this would kill X down to
		 * s/t_mbi (i.e. one packet in 64 seconds).
		 * To avoid such drastic reduction, we approximate X_recv as
		 * the number of bytes since last feedback.
		 * This is a safe fallback, since X is bounded above by X_calc.
		 */
		if (hc->rx_x_recv > 0)
			break;
		/* fall through */
	case CCID3_FBACK_PERIODIC:
		delta = ktime_us_delta(now, hc->rx_tstamp_last_feedback);
		if (delta <= 0)
			delta = 1;
		hc->rx_x_recv = scaled_div32(hc->rx_bytes_recv, delta);
		break;
	default:
		return;
	}

	ccid3_pr_debug("Interval %lldusec, X_recv=%u, 1/p=%u\n", delta,
		       hc->rx_x_recv, hc->rx_pinv);

	hc->rx_tstamp_last_feedback = now;
	hc->rx_last_counter	    = dccp_hdr(skb)->dccph_ccval;
	hc->rx_bytes_recv	    = 0;

	dp->dccps_hc_rx_insert_options = 1;
	dccp_send_ack(sk);
}