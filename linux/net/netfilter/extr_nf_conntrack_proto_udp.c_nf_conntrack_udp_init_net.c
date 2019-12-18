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
struct nf_udp_net {int /*<<< orphan*/ * timeouts; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int UDP_CT_MAX ; 
 struct nf_udp_net* nf_udp_pernet (struct net*) ; 
 int /*<<< orphan*/ * udp_timeouts ; 

void nf_conntrack_udp_init_net(struct net *net)
{
	struct nf_udp_net *un = nf_udp_pernet(net);
	int i;

	for (i = 0; i < UDP_CT_MAX; i++)
		un->timeouts[i] = udp_timeouts[i];
}