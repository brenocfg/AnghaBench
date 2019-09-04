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
struct TYPE_3__ {int dctcp_enabled; int /*<<< orphan*/  dctcp_ab_tot; int /*<<< orphan*/  dctcp_ab_ecn; int /*<<< orphan*/  dctcp_alpha; scalar_t__ dctcp_ce_state; } ;
union tcp_cc_info {TYPE_1__ dctcp; } ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct dctcp {int /*<<< orphan*/  acked_bytes_total; int /*<<< orphan*/  acked_bytes_ecn; int /*<<< orphan*/  dctcp_alpha; scalar_t__ ce_state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * icsk_ca_ops; } ;

/* Variables and functions */
 int INET_DIAG_DCTCPINFO ; 
 int INET_DIAG_VEGASINFO ; 
 int /*<<< orphan*/  dctcp_reno ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct dctcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t dctcp_get_info(struct sock *sk, u32 ext, int *attr,
			     union tcp_cc_info *info)
{
	const struct dctcp *ca = inet_csk_ca(sk);

	/* Fill it also in case of VEGASINFO due to req struct limits.
	 * We can still correctly retrieve it later.
	 */
	if (ext & (1 << (INET_DIAG_DCTCPINFO - 1)) ||
	    ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		memset(&info->dctcp, 0, sizeof(info->dctcp));
		if (inet_csk(sk)->icsk_ca_ops != &dctcp_reno) {
			info->dctcp.dctcp_enabled = 1;
			info->dctcp.dctcp_ce_state = (u16) ca->ce_state;
			info->dctcp.dctcp_alpha = ca->dctcp_alpha;
			info->dctcp.dctcp_ab_ecn = ca->acked_bytes_ecn;
			info->dctcp.dctcp_ab_tot = ca->acked_bytes_total;
		}

		*attr = INET_DIAG_DCTCPINFO;
		return sizeof(info->dctcp);
	}
	return 0;
}