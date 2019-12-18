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
struct sock {int dummy; } ;
struct dn_scp {unsigned long nsp_srtt; unsigned long nsp_rttvar; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 

__attribute__((used)) static void dn_nsp_rtt(struct sock *sk, long rtt)
{
	struct dn_scp *scp = DN_SK(sk);
	long srtt = (long)scp->nsp_srtt;
	long rttvar = (long)scp->nsp_rttvar;
	long delta;

	/*
	 * If the jiffies clock flips over in the middle of timestamp
	 * gathering this value might turn out negative, so we make sure
	 * that is it always positive here.
	 */
	if (rtt < 0)
		rtt = -rtt;
	/*
	 * Add new rtt to smoothed average
	 */
	delta = ((rtt << 3) - srtt);
	srtt += (delta >> 3);
	if (srtt >= 1)
		scp->nsp_srtt = (unsigned long)srtt;
	else
		scp->nsp_srtt = 1;

	/*
	 * Add new rtt varience to smoothed varience
	 */
	delta >>= 1;
	rttvar += ((((delta>0)?(delta):(-delta)) - rttvar) >> 2);
	if (rttvar >= 1)
		scp->nsp_rttvar = (unsigned long)rttvar;
	else
		scp->nsp_rttvar = 1;

	/* printk(KERN_DEBUG "srtt=%lu rttvar=%lu\n", scp->nsp_srtt, scp->nsp_rttvar); */
}