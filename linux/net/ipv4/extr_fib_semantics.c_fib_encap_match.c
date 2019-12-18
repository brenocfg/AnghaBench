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
typedef  scalar_t__ u16 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct lwtunnel_state {int dummy; } ;
struct fib_nh {int /*<<< orphan*/  fib_nh_lws; } ;
struct fib_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ LWTUNNEL_ENCAP_NONE ; 
 int /*<<< orphan*/  lwtstate_free (struct lwtunnel_state*) ; 
 int lwtunnel_build_state (scalar_t__,struct nlattr*,int /*<<< orphan*/ ,struct fib_config const*,struct lwtunnel_state**,struct netlink_ext_ack*) ; 
 int lwtunnel_cmp_encap (struct lwtunnel_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib_encap_match(u16 encap_type,
			   struct nlattr *encap,
			   const struct fib_nh *nh,
			   const struct fib_config *cfg,
			   struct netlink_ext_ack *extack)
{
	struct lwtunnel_state *lwtstate;
	int ret, result = 0;

	if (encap_type == LWTUNNEL_ENCAP_NONE)
		return 0;

	ret = lwtunnel_build_state(encap_type, encap, AF_INET,
				   cfg, &lwtstate, extack);
	if (!ret) {
		result = lwtunnel_cmp_encap(lwtstate, nh->fib_nh_lws);
		lwtstate_free(lwtstate);
	}

	return result;
}