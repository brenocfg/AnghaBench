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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_nat_ipv4_ops ; 
 int nf_nat_ipv4_register_fn (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_nat_ipv4_unregister_fn (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipt_nat_register_lookups(struct net *net)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(nf_nat_ipv4_ops); i++) {
		ret = nf_nat_ipv4_register_fn(net, &nf_nat_ipv4_ops[i]);
		if (ret) {
			while (i)
				nf_nat_ipv4_unregister_fn(net, &nf_nat_ipv4_ops[--i]);

			return ret;
		}
	}

	return 0;
}