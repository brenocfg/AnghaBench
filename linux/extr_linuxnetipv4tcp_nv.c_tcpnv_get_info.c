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
struct TYPE_2__ {int tcpv_enabled; int /*<<< orphan*/  tcpv_minrtt; int /*<<< orphan*/  tcpv_rtt; int /*<<< orphan*/  tcpv_rttcnt; } ;
union tcp_cc_info {TYPE_1__ vegas; } ;
typedef  int u32 ;
struct tcpvegas_info {int dummy; } ;
struct tcpnv {int /*<<< orphan*/  nv_min_rtt; int /*<<< orphan*/  nv_last_rtt; int /*<<< orphan*/  nv_rtt_cnt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int INET_DIAG_VEGASINFO ; 
 struct tcpnv* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static size_t tcpnv_get_info(struct sock *sk, u32 ext, int *attr,
			     union tcp_cc_info *info)
{
	const struct tcpnv *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabled = 1;
		info->vegas.tcpv_rttcnt = ca->nv_rtt_cnt;
		info->vegas.tcpv_rtt = ca->nv_last_rtt;
		info->vegas.tcpv_minrtt = ca->nv_min_rtt;

		*attr = INET_DIAG_VEGASINFO;
		return sizeof(struct tcpvegas_info);
	}
	return 0;
}