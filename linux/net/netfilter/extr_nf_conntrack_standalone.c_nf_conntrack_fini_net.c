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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_INET ; 
 scalar_t__ enable_hooks ; 
 int /*<<< orphan*/  nf_conntrack_standalone_fini_proc (struct net*) ; 
 int /*<<< orphan*/  nf_conntrack_standalone_fini_sysctl (struct net*) ; 
 int /*<<< orphan*/  nf_ct_netns_put (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_conntrack_fini_net(struct net *net)
{
	if (enable_hooks)
		nf_ct_netns_put(net, NFPROTO_INET);

	nf_conntrack_standalone_fini_proc(net);
	nf_conntrack_standalone_fini_sysctl(net);
}