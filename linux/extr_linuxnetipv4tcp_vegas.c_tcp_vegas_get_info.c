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
struct TYPE_2__ {int /*<<< orphan*/  tcpv_minrtt; int /*<<< orphan*/  tcpv_rtt; int /*<<< orphan*/  tcpv_rttcnt; int /*<<< orphan*/  tcpv_enabled; } ;
union tcp_cc_info {TYPE_1__ vegas; } ;
typedef  int u32 ;
struct vegas {int /*<<< orphan*/  minRTT; int /*<<< orphan*/  baseRTT; int /*<<< orphan*/  cntRTT; int /*<<< orphan*/  doing_vegas_now; } ;
struct tcpvegas_info {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int INET_DIAG_VEGASINFO ; 
 struct vegas* inet_csk_ca (struct sock*) ; 

size_t tcp_vegas_get_info(struct sock *sk, u32 ext, int *attr,
			  union tcp_cc_info *info)
{
	const struct vegas *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabled = ca->doing_vegas_now,
		info->vegas.tcpv_rttcnt = ca->cntRTT,
		info->vegas.tcpv_rtt = ca->baseRTT,
		info->vegas.tcpv_minrtt = ca->minRTT,

		*attr = INET_DIAG_VEGASINFO;
		return sizeof(struct tcpvegas_info);
	}
	return 0;
}