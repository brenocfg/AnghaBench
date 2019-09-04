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
struct tcp_options_received {int rcv_tsecr; } ;
struct TYPE_2__ {scalar_t__ sysctl_tcp_ecn; } ;
struct net {TYPE_1__ ipv4; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_FEATURE_ECN ; 
 int TS_OPT_ECN ; 
 int dst_feature (struct dst_entry const*,int /*<<< orphan*/ ) ; 

bool cookie_ecn_ok(const struct tcp_options_received *tcp_opt,
		   const struct net *net, const struct dst_entry *dst)
{
	bool ecn_ok = tcp_opt->rcv_tsecr & TS_OPT_ECN;

	if (!ecn_ok)
		return false;

	if (net->ipv4.sysctl_tcp_ecn)
		return true;

	return dst_feature(dst, RTAX_FEATURE_ECN);
}