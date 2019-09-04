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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nf_proto_net {int dummy; } ;
struct nf_icmp_net {int /*<<< orphan*/  timeout; struct nf_proto_net pn; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int icmp_kmemdup_sysctl_table (struct nf_proto_net*,struct nf_icmp_net*) ; 
 struct nf_icmp_net* icmp_pernet (struct net*) ; 
 int /*<<< orphan*/  nf_ct_icmp_timeout ; 

__attribute__((used)) static int icmp_init_net(struct net *net, u_int16_t proto)
{
	struct nf_icmp_net *in = icmp_pernet(net);
	struct nf_proto_net *pn = &in->pn;

	in->timeout = nf_ct_icmp_timeout;

	return icmp_kmemdup_sysctl_table(pn, in);
}