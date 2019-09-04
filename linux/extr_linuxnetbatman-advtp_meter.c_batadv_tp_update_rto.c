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
typedef  long u32 ;
struct batadv_tp_vars {int srtt; int rttvar; int rto; } ;

/* Variables and functions */

__attribute__((used)) static void batadv_tp_update_rto(struct batadv_tp_vars *tp_vars,
				 u32 new_rtt)
{
	long m = new_rtt;

	/* RTT update
	 * Details in Section 2.2 and 2.3 of RFC6298
	 *
	 * It's tricky to understand. Don't lose hair please.
	 * Inspired by tcp_rtt_estimator() tcp_input.c
	 */
	if (tp_vars->srtt != 0) {
		m -= (tp_vars->srtt >> 3); /* m is now error in rtt est */
		tp_vars->srtt += m; /* rtt = 7/8 srtt + 1/8 new */
		if (m < 0)
			m = -m;

		m -= (tp_vars->rttvar >> 2);
		tp_vars->rttvar += m; /* mdev ~= 3/4 rttvar + 1/4 new */
	} else {
		/* first measure getting in */
		tp_vars->srtt = m << 3;	/* take the measured time to be srtt */
		tp_vars->rttvar = m << 1; /* new_rtt / 2 */
	}

	/* rto = srtt + 4 * rttvar.
	 * rttvar is scaled by 4, therefore doesn't need to be multiplied
	 */
	tp_vars->rto = (tp_vars->srtt >> 3) + tp_vars->rttvar;
}