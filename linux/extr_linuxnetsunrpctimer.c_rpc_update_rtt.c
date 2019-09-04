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
struct rpc_rtt {int /*<<< orphan*/ * sdrtt; int /*<<< orphan*/ * srtt; } ;

/* Variables and functions */
 long RPC_RTO_MIN ; 

void rpc_update_rtt(struct rpc_rtt *rt, unsigned int timer, long m)
{
	long *srtt, *sdrtt;

	if (timer-- == 0)
		return;

	/* jiffies wrapped; ignore this one */
	if (m < 0)
		return;

	if (m == 0)
		m = 1L;

	srtt = (long *)&rt->srtt[timer];
	m -= *srtt >> 3;
	*srtt += m;

	if (m < 0)
		m = -m;

	sdrtt = (long *)&rt->sdrtt[timer];
	m -= *sdrtt >> 2;
	*sdrtt += m;

	/* Set lower bound on the variance */
	if (*sdrtt < RPC_RTO_MIN)
		*sdrtt = RPC_RTO_MIN;
}