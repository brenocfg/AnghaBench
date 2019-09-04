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
struct nf_proto_net {int /*<<< orphan*/  users; } ;
struct nf_udp_net {int /*<<< orphan*/ * timeouts; struct nf_proto_net pn; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int UDP_CT_MAX ; 
 int udp_kmemdup_sysctl_table (struct nf_proto_net*,struct nf_udp_net*) ; 
 struct nf_udp_net* udp_pernet (struct net*) ; 
 int /*<<< orphan*/ * udp_timeouts ; 

__attribute__((used)) static int udp_init_net(struct net *net, u_int16_t proto)
{
	struct nf_udp_net *un = udp_pernet(net);
	struct nf_proto_net *pn = &un->pn;

	if (!pn->users) {
		int i;

		for (i = 0; i < UDP_CT_MAX; i++)
			un->timeouts[i] = udp_timeouts[i];
	}

	return udp_kmemdup_sysctl_table(pn, un);
}