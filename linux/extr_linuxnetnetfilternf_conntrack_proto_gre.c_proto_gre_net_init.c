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
 int /*<<< orphan*/  nf_conntrack_l4proto_gre4 ; 
 int nf_ct_l4proto_pernet_register_one (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int proto_gre_net_init(struct net *net)
{
	int ret = 0;

	ret = nf_ct_l4proto_pernet_register_one(net,
						&nf_conntrack_l4proto_gre4);
	if (ret < 0)
		pr_err("nf_conntrack_gre4: pernet registration failed.\n");
	return ret;
}