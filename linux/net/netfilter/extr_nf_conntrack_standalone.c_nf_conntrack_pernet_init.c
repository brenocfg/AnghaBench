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
struct TYPE_2__ {int sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_INET ; 
 scalar_t__ enable_hooks ; 
 int /*<<< orphan*/  nf_conntrack_cleanup_net (struct net*) ; 
 int nf_conntrack_init_net (struct net*) ; 
 int /*<<< orphan*/  nf_conntrack_standalone_fini_proc (struct net*) ; 
 int /*<<< orphan*/  nf_conntrack_standalone_fini_sysctl (struct net*) ; 
 int nf_conntrack_standalone_init_proc (struct net*) ; 
 int nf_conntrack_standalone_init_sysctl (struct net*) ; 
 int nf_ct_netns_get (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_conntrack_pernet_init(struct net *net)
{
	int ret;

	net->ct.sysctl_checksum = 1;

	ret = nf_conntrack_standalone_init_sysctl(net);
	if (ret < 0)
		return ret;

	ret = nf_conntrack_standalone_init_proc(net);
	if (ret < 0)
		goto out_proc;

	ret = nf_conntrack_init_net(net);
	if (ret < 0)
		goto out_init_net;

	if (enable_hooks) {
		ret = nf_ct_netns_get(net, NFPROTO_INET);
		if (ret < 0)
			goto out_hooks;
	}

	return 0;

out_hooks:
	nf_conntrack_cleanup_net(net);
out_init_net:
	nf_conntrack_standalone_fini_proc(net);
out_proc:
	nf_conntrack_standalone_fini_sysctl(net);
	return ret;
}