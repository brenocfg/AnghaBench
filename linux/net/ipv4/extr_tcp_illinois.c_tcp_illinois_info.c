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
struct TYPE_2__ {int tcpv_enabled; scalar_t__ tcpv_rtt; int /*<<< orphan*/  tcpv_rttcnt; int /*<<< orphan*/  tcpv_minrtt; } ;
union tcp_cc_info {TYPE_1__ vegas; } ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct tcpvegas_info {int dummy; } ;
struct sock {int dummy; } ;
struct illinois {scalar_t__ sum_rtt; int /*<<< orphan*/  base_rtt; int /*<<< orphan*/  cnt_rtt; } ;

/* Variables and functions */
 int INET_DIAG_VEGASINFO ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 struct illinois* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static size_t tcp_illinois_info(struct sock *sk, u32 ext, int *attr,
				union tcp_cc_info *info)
{
	const struct illinois *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabled = 1;
		info->vegas.tcpv_rttcnt = ca->cnt_rtt;
		info->vegas.tcpv_minrtt = ca->base_rtt;
		info->vegas.tcpv_rtt = 0;

		if (info->vegas.tcpv_rttcnt > 0) {
			u64 t = ca->sum_rtt;

			do_div(t, info->vegas.tcpv_rttcnt);
			info->vegas.tcpv_rtt = t;
		}
		*attr = INET_DIAG_VEGASINFO;
		return sizeof(struct tcpvegas_info);
	}
	return 0;
}