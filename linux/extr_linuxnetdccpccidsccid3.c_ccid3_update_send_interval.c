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
typedef  int u64 ;
struct ccid3_hc_tx_sock {scalar_t__ tx_t_ipi; int tx_x; scalar_t__ tx_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG_ON (int) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ scaled_div32 (int,int) ; 

__attribute__((used)) static void ccid3_update_send_interval(struct ccid3_hc_tx_sock *hc)
{
	hc->tx_t_ipi = scaled_div32(((u64)hc->tx_s) << 6, hc->tx_x);

	DCCP_BUG_ON(hc->tx_t_ipi == 0);
	ccid3_pr_debug("t_ipi=%u, s=%u, X=%u\n", hc->tx_t_ipi,
		       hc->tx_s, (unsigned int)(hc->tx_x >> 6));
}