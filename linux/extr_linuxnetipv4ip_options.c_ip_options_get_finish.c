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
struct net {int dummy; } ;
struct TYPE_2__ {int optlen; int /*<<< orphan*/ * __data; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPOPT_END ; 
 scalar_t__ ip_options_compile (struct net*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ip_options_rcu*) ; 

__attribute__((used)) static int ip_options_get_finish(struct net *net, struct ip_options_rcu **optp,
				 struct ip_options_rcu *opt, int optlen)
{
	while (optlen & 3)
		opt->opt.__data[optlen++] = IPOPT_END;
	opt->opt.optlen = optlen;
	if (optlen && ip_options_compile(net, &opt->opt, NULL)) {
		kfree(opt);
		return -EINVAL;
	}
	kfree(*optp);
	*optp = opt;
	return 0;
}